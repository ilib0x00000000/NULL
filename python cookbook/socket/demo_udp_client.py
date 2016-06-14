#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-14 16:20:29 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
使用UDP协议通信的客户端
"""

import socket

BUFFER_SIZE = 4096

# 创建一个socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

SERVER_HOST = 'localhost'
SERVER_PORT = 20200

message = 'This is a message, It will be repeated'

try:
	'''使用UDP协议发送信息后，返回发送信息的长度
	'''
	sent = client.sendto(message, (SERVER_HOST, SERVER_PORT))

	print sent
	print type(sent)

	data, server = client.recvfrom(BUFFER_SIZE)

	print 'from ',server, ' : ',data
finally:
	client.close()
