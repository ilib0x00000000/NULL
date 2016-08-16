#/usr/bin/env  python
#-*- coding:utf-8 -*-

import socket
import signal
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



if __name__ == '__main__':
	# simple_response() # Time taken for tests:   5.608 seconds
	process_response()


'''
插曲：在使用ab测压时发生错误：apr_pollset_poll: The timeout specified has expired (70007)
ab -n 100000 -c 4 -k http://localhost:50000/
'''