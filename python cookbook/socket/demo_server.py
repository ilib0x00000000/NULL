#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-13 15:49:52 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
socket编程(单线程版)：
		1. 创建一个socket			socket.socket
		2. 关联到主机				server.bind()
		3. 设置成服务器模式			server.listen(n)
		4. 等待客户端请求 			server.accept()
		5. 关闭连接					connection.close()

说明：
		listen中的参数n表示排队等待处理的连接的数目(已连接上，等待处理)，超过这个数目之后，系统会拒绝新的连接
"""


import sys
import socket

BUFFER_SIZE = 1024

# 创建一个server
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_host = sys.argv[1]
server_port = 20200

# 将server关联到主机
# 主机的地址由启动参数给出
server.bind((server_host, server_port))

# 将server设置为服务器模式
server.listen(1)

while True:
	# 等待客户端的请求
	connection, client = server.accept()

	try:
		while True:
			data = connection.recv(BUFFER_SIZE)

			if data:
				print 'form ', client, ' : ', data
				connection.sendall(data)
			else:
				break
	finally:
		# 关闭通信信道
		connection.close()