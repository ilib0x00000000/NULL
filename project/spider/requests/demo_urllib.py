#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-04 16:02:07 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

import os
import sys
import urllib 
import urllib2
import cookielib



def url_open():
	# urlopen(url, data, timeout)一般接受3个参数
	response = urllib2.urlopen('http://www.baidu.com')

	print response.read().encode('utf-8')


def request_urlopen():
	url = 'http://www.baidu.com'
	requests = urllib2.Request(url)

	response = urllib2.urlopen(requests)

	return response


def simple_post_login():
	"""
		POST请求：
			参数使用urllib.urlencode()编码，

			构建Request对象：urllib2.Request(url, data)
			发送request请求：urllib2.urlopen()
	"""
	url = ''
	values = {}
	values['account'] = ''
	values['password'] = ''
	data = urllib.urlencode(values)

	# 这里实现的是POST请求
	request = urllib2.Request(url, data)
	response = urllib2.urlopen(request)

	print response.read()


def simple_get_login():
	"""
		GET请求方式：
			参数使用urllib.urlencode()编码，
			编码后的参数直接添加到url后面

			构建Request对象：urllib2.Request(url)
			发送request： urllib2.urlopen()
	"""
	values = {}
	values['account'] = ''
	values['password'] = ''
	data = urllib.urlencode(values)

	url = ''.join(['http://....?',data])
	print url

	request = urllib2.Request(url)
	response = urllib2.urlopen(request)

	return response 


def login_with_headers():
	url = ''
	values = {}
	values['account'] = ''
	values['password'] = ''

	# headers常用属性
	headers = {}
	headers['User-Agent'] = ''								# 浏览器识别方式
	headers['Content-Type'] = ''							# 在使用REST接口时，服务器检查该值，用来确定HTTP body中的内容怎么解析
	headers['application/xml'] = ''							# 在 XML RPC，如RESTful/SOAP调用时使用
	headers['application/json'] = ''						# 在JSON RPC调用时使用
	headers['application/x-www-form-urlencoded'] = ''		# 浏览器提交表单时使用


def login_with_proxy():
	"""
		有的网站会检测一段时间内某个IP的访问次数，可以设置一个代理服务器
	"""
	enable_proxy = True

	proxy = {}
	proxy['http'] = 'http://some-proxy.com:8080'
	proxy_handler = urllib2.ProxyHandler(proxy)

	no_proxy_handler = {}

	if enable_proxy:
		opener = urllib2.build_opener(proxy_handler)
	else:
		opener = urllib2.build_opener(no_proxy_handler)

	urllib2.install_opener(opener)


def login_with_cookie():
	url = ''

	cookie = cookielib.CookieJar()			# 声明一个CookieJar对象实例来保存cookie
	handler = urllib2.HTTPCookieProcessor(cookie)	# 利用urllib2库的HTTPCookieProcessor对象来创建cookie处理器
	opener = urllib2.build_opener(handler)		# 通过handler来构建opener

	response = opener.open(url)

	return response


def login_with_save_cookie():
	url = ''

	file_name = ''										# 保存cookie的文件
	cookie = cookielib.MozillaCookieJar(file_name)		# 声明一个MozillaCookieJar对象保存cookie，之后写入文件

	handler = urllib2.HTTPCookieProcessor(cookie)		# 通过HTTPCookieProcessor创建cookie处理器

	opener = urllib2.build_opener(handler)				# 通过handler来构建opener
	opener.open(url)

	cookie.save(ignore_discard=True, ignore_expires=True)
	# 保存cookie到文件
	# ignore_discard: 即使cookies将被丢弃也将它保存下来
	# ignore_expires: 如果该文件中cookis已经存在，则覆盖原文件写入


def login_with_load_cookie():
	url = ''

	cookie = cookielib.MozillaCookieJar()									# 创建MozillaCookieJar对象
	cookie.load(file_name, ignore_discard=True, ignore_expires=True)		# 读取cookies文件

	request = urllib2.Request(url)											# 构建request对象

	handler = urllib2.HTTPCookieProcessor(cookie)							# 创建cookie处理器
	opener = urllib2.build_opener(handler)									# 创建opener

	response = opener.open(request)

	return response


def test():
	init_url = 'http://222.24.62.120/'

	# 获得cookie
	cookie = cookielib.CookieJar()
	handler = urllib2.HTTPCookieProcessor(cookie)
	opener = urllib2.build_opener(handler)
	response = opener.open(init_url)

	with open('login.html', 'w+b') as f:
		f.write(response.read())
	# print cookie.set_cookie
	
	url = ''.join([init_url, 'default2.aspx'])
	
	paras = {}
	paras['txtUserName'] = os.getenv('LOGIN_NAME')
	paras['TextBox2'] = os.getenv('LOGIN_PASSWD')
	# 这里出现验证码
	# paras['txtSecretCode']
	paras['RadioButtonList1'] = '学生'
	data = urllib.urlencode(paras)

	request = urllib2.Request(url, data)

	response = opener.open(request)

	return response

if __name__ == '__main__':
	response = test()

	print response.url