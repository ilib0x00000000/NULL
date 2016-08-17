#/usr/bin/env  python
#-*- coding:utf-8 -*-

'''
以下代码测试环境：
	RAM:    5.7 GiB
	OS:     Ubuntu 14.04 LTS 64bit
	CPU:    Intel® Core™ i3-2350M CPU @ 2.30GHz × 4 
	Python: Python 2.7.6
'''

import Queue
import socket
import signal
import select
import threading
import multiprocessing


HOST = '127.0.0.1'
PORT = 50000
BUFFER_SIZE = 1024

response = 'HTTP/1.1 200 OK\r\nConnection:Close\r\nContent-Length:11\r\n\r\nHello World'

'''
最简单的并发
'''
def simple_response():
	# 1.创建一个socket
	server = socket.socket()

	# 2.绑定主机和端口
	server.bind((HOST, PORT))

	# 3.监听请求
	server.listen(1024)

	while True:
		client, client_addr = server.accept()
		request = client.recv(BUFFER_SIZE)
		client.send(response)
		client.close()



'''
多进程：
一个请求对应一个进程，但是进程太占资源，每个请求的资源也是独立的，无法共享，而且进程的上下文切换成本很高
'''
def handler(client):
	data = client.recv(BUFFER_SIZE)
	client.send(response)
	client.close()
def process_response():

	server = socket.socket()
	server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	server.bind((HOST, PORT))

	server.listen(1024)

	# 多进程中的子进程执行完毕后并不会死掉，而是变成僵尸进程，等待主线程挂掉以后才会死掉
	# 下面这段代码解决这个问题
	signal.signal(signal.SIGCHLD, signal.SIG_IGN)

	while True:
		client, client_addr = server.accept()

		process = multiprocessing.Process(target=handler, args=(client, ))
		process.start()



'''
线程池:构建一个队列（线程安全）将接受到的连接请求全部放到队列中
多线程的程序主要是维护队列
'''
def handler2(queue):
	client = queue.get()
	data = client.recv(BUFFER_SIZE)
	client.send(response)
	client.close()
def multithread_response():
	server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	server.bind((HOST, PORT))
	server.listen(1024)

	# 构建一个队列
	queue = Queue.Queue()
	processor = 4 # CPU的核数

	# 创建同CPU核数一样多的线程个数
	for i in range(0, processor):
		thread = threading.Thread(target=handler2, args=(queue,))
		thread.daemon = True
		thread.start()

	while True:
		client, client_addr = server.accept()
		queue.put(client)



'''
epoll:
'''
def epoll_response():
	server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	server.setblocking(False)
	server.bind((HOST,PORT))
	server.listen(1024)

	READ_ONLY = select.EPOLLIN | select.EPOLLPRI
	epoll = select.epoll()
	epoll.register(server, READ_ONLY)

	timeout = 60

	fd_to_socket = {server.fileno():server}

	while True:
		events = epoll.poll(timeout)
		for fd,flag in events:
			sock = fd_to_socket[fd]
			if flag & READ_ONLY:
				if sock is server:
					conn, client_address = sock.accept()
					conn.setblocking(False)
					fd_to_socket[conn.fileno()] = conn
					epoll.register(conn, READ_ONLY)
				else:
					request = sock.recv(BUFFER_SIZE)
					sock.send(response)
					sock.close()
					del fd_to_socket[fd]



if __name__ == '__main__':
	# simple_response()         
		# 10W: Time taken for tests:   5.608 seconds 	
		# 100W:Time taken for tests:   137.060 seconds

	# process_response()        # 在使用ab测压时发生错误：apr_pollset_poll: The timeout specified has expired (70007)
	
	# multithread_response()  	# 在使用ab测压时发生错误：apr_pollset_poll: The timeout specified has expired (70007)
	
	epoll_response() 		    
		# 10W: Time taken for tests:   6.998 seconds 	
		# 100W:Time taken for tests:   114.429 seconds


'''
ab -n 100000 -c 4 -k http://localhost:50000/
'''