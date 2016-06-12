#/usr/bin/env  python
#-*- coding:utf-8 -*-

"""
socket 直接访问本地C套接字库
select 可以同时监视多个套接字，允许网络服务器同时与多个客户通信
SocketServer框架
asyncore 实现了异步网络栈
asynchat 框架封装了asyncore
"""

import sys
import socket
import struct
import urlparse
import binascii

'''
套接字控制两层协议（网络层和传输层）：
		网络层：
				AF_INET 		IPv4协议
				AF_INET6		IPv6协议
				AF_UNIX			UNIX域套接字，POSIX兼容系统上的进程间的通信协议

		传输层：
				SOCK_DGRAM			UDP协议
				SOCK_STREAM			TCP协议
'''

def test_gethostname():
	# 获得本机的主机名
	print socket.gethostname()


def test_gethostbyname():
	# 通过域名获得IP地址
	for host in ['www.baidu.com', 'www.sina.com', 'www.google.com']:
		try:
			print host, ' : ', socket.gethostbyname(host)
		except socket.error, msg:
			print host, ' : ', msg


def test_gethostbyname_ex():
	# 查看服务器更详细的信息
	host = 'www.baidu.com'
	try:
		print socket.gethostbyname_ex(host)
	except socket.error:
		pass


def test_gethostbyaddr():
	# 通过IP地址获得主机名
	for host in ['119.75.218.70', '121.194.0.239', '216.58.197.100']:
		try:
			print socket.gethostbyaddr(host)
		except socket.error:
			pass


def test_getservbyport():
	# 通过端口查看服务器开启了哪些服务
	for port in [21, 25, 70, 80, 110, 143, 443, 993, 995]:
		print urlparse.urlunparse((socket.getservbyport(port), 'baidu.com', '/', '', '', ''))


def test_getaddrinfo():
	families = dict((getattr(socket, n), n) for n in dir(socket) if n.startswith('AF_'))
	types = dict((getattr(socket, n), n) for n in dir(socket) if n.startswith('SOCK_'))
	protocols = dict((getattr(socket, n), n) for n in dir(socket) if n.startswith('IPPROTO_'))

	family, socktype, proto, canonname, sockaddr = socket.getaddrinfo('www.baidu.com', 'http')[0]

	print 'Family  :  ', families[family]
	print 'Type    :  ', types[socktype]
	print 'Protocol:  ', protocols[proto]
	print 'address :  ', sockaddr

	family, socktype, proto, canonname, sockaddr = socket.getaddrinfo('www.baidu.com', 'http')[1]

	print 'Family  :  ', families[family]
	print 'Type    :  ', types[socktype]
	print 'Protocol:  ', protocols[proto]
	print 'address :  ', sockaddr


def test_ipconvert():
	for ip_string in ['192.168.1.100', '127.0.0.1']:
		packed_ip = socket.inet_aton(ip_string)
		print 'original ip:          ',  ip_string
		print 'inet_aton(ip_string): ',  packed_ip
		print 'hexlify:              ',  binascii.hexlify(packed_ip)
		print 'unpacked:             ',  socket.inet_ntoa(packed_ip)


if __name__ == '__main__':
	test_gethostname()
	test_gethostbyname()
	test_gethostbyname_ex()
	test_gethostbyaddr()
	test_getservbyport()
	test_getaddrinfo()
	test_ipconvert()