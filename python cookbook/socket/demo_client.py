#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-13 16:05:29 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

import sys
import socket

# 设置缓冲区长度
BUFFER_SIZE = 1024

# 创建一个socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_host = sys.argv[1]
server_port = 20200

# 连接server
client.connect((server_host, server_port))

try:
	message = ''' 
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
		this is the message, it will be back this is the message, it will be back
	'''

	client.sendall(message)

	data = client.recv(BUFFER_SIZE)

	while True:
		print data
		print '\n--------------------------------------------------------------\n'
		'''如果接收的数据的长度小于缓冲区的长度，说明返回的数据已经结束
		'''
		if len(data)<BUFFER_SIZE:
			break
		else:
			data = client.recv(BUFFER_SIZE)
finally:
	client.close()

