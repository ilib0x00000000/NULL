#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-14 16:10:14 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
使用UDP协议，不需要监听和接受连接，只需要使用bind()关联一个主机即可
			1. socket.socket()
			2. server.bind()
			3. server.recvfrom() 	接收信息
			4. server.sendto()  	发送信息		
"""

import socket

# 缓冲区长度
BUFFER_SIZE = 4096

# 创建一个UDP socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

SERVER_HOST = 'localhost'
SERVER_PORT = 20200

# 关联主机
server.bind((SERVER_HOST, SERVER_PORT))

while True:
	data, client = server.recvfrom(BUFFER_SIZE)
	print 'from ', client, ' : ', data

	if data:
		sent = server.sendto(data, client)
		print sent
		print type(sent)