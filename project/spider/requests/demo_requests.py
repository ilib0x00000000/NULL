#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-06 20:30:07 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
request的几种常用请求方式
			get
			post
			put
			delete
			head
			options
"""

import os
import json
import requests


def http_get():
	url = ''

	# get携带的参数
	payload = {}
	payload['key'] = 'value'

	# 请求的首部
	headers = {}
	headers['User-Agent'] = ''

	# 如果要获取来自服务器的原始套接字，需要在请求中指定参数stream=True
	# response.raw得到原始套接字
	response = requests.get(url, params=payload, headers=headers)

	return response


def http_post():
	url = ''
	PARA_JSON = None
	file_name = ''
	SSL_REQUEST = None

	# 请求首部
	headers = {}
	headers['User-Agent'] = ''

	# 请求数据
	data = {}
	data['key'] = 'value'

	# 设置代理
	proxies = {}
	proxies['http'] = ''
	proxies['https'] = ''

	# 如果请求中上传文件
	files = {}
	files['file'] = open(file_name, 'rb')

	# 如果有cookies
	cookies = None

	# 如果服务器接受的参数是json形式的
	if PARA_JSON:
		response = requests.post(url, headers=headers, data=json.dumps(data), files=files, proxies=proxies)
	elif SSL_REQUEST:
		# 如果请求是https，则需要在请求中指定参数verify=True
		response = requests.post(url, data=data, headers=headers, files=files, verify=True, proxies = proxies)
	elif cookies:
		response = requests.post(url, data=data, headers=headers, files=files, proxies = proxies, cookies=cookies)
	else:
		response = requests.post(url, data=data, headers=headers, files=files, proxies = proxies)

	return response



def http_session():
	url = ''

	session = requests.Session()

	s.headers = {}
	s.headers['User-Agent'] = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:46.0) Gecko/20100101 Firefox/46.0'

	response = s.get(url)

	return response



def login_zhihu():
	"""
		1. 登录知乎首页，获得cookie
		2. 登录知乎
	"""
	url = 'http://www.zhihu.com/'

	headers = {}
	headers['User-Agent'] = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:46.0) Gecko/20100101 Firefox/46.0'

	# response = requests.get(url, headers=headers)
	session = requests.Session()
	response = session.get(url,headers=headers)

	# 获得cookies
	cookie = response.cookies

	# 携带数据信息
	data = {}
	data['account'] = os.getenv('LOGIN_NAME')
	data['password'] = os.getenv('LOGIN_PASSWD')
	data['remember_me'] = False

	# 目标地址
	des_url = 'http://www.zhihu.com/login/phone_num'

	response = session.post(des_url, headers=headers, data=json.dumps(data), cookies=cookie, verify=True)

	if response.status_code == 200:
		with open('zhihu.html', 'w+b') as f:
			f.write(response.text)


if __name__ == '__main__':
	login_zhihu()