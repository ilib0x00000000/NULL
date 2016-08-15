# /usr/bin/env  python
# -*- coding:utf-8 -*-

import time
import SocketServer

'''
BaseServer:   仅用于继承
ForkingMixIn/ThreadingMixIn:  仅用于继承

Server有如下几种：
	TCPServer/UDPServer:                   基础的网络同步TCP/UDP服务器
	UnixStreamServer/UnixDatagramServer:   基于文件的TCP/UDP服务器
	ForkingTCPServer/ForkingUDPServer:     ForkingMixIn和TCPServer/UDPServer的组合(多进程Server)
	ThreadingTCPServer/ThreadingUDPServer: ThreadingMixIn和TCPServer/UDPServer的组合(多线程Server)

Handler:
	BaseRequestHandler: 仅用于继承
	StreamRequestHandler/DatagramRequestHandler:
'''

HOST = 'localhost'
PORT = 55555

# 继承StreamRequestHandler，处理TCP请求
class TcpRequestHandler(SocketServer.StreamRequestHandler):
	# 重写handle方法
	def handle(self):
		'''
			继承下来的handler中有几个属性：
			self.client_address: 客户端IP
			self.rfile:          接受的请求（类文件对象）
			self.wfile:          发送的响应（类文件对象）
		'''
		print '...connectd from: ', self.client_address
		self.wfile.write('[%s] %s' % (time.ctime(), self.rfile.readline()))


def create_server():
	# 创建一个单线程的Server
	tcp_server = SocketServer.TCPServer((HOST,PORT), TcpRequestHandler)
	print 'waiting for connection...'
	tcp_server.serve_forever()	

def create_threading_server():
	# 创建一个多线程的Server
	thread_server = SocketServer.ThreadingTCPServer((HOST,PORT), TcpRequestHandler)
	thread_server.serve_forever()

def create_fork_server():
	# 创建一个多进程的Server
	fork_server = SocketServer.ForkingTCPServer((HOST, PORT), TcpRequestHandler)
	fork_server.serve_forever()


'''
Server的类型必须对应相应的Handler
'''