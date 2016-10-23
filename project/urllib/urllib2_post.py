#!/usr/bin/env  python
# -*- coding:utf-8 -*-


'''
使用urllib2库构造POST请求
构造POST请求需要3部分
POST request：
	URL
	data
	headers
'''

import os
import urllib
import urllib2
import cookielib

## 准备request的组成部分
# 1. url
url = ''

# 2. data(POST请求要携带的数据)
values = {}
values['key'] = 'value'
data = urllib.urlencode(values)

# 3. headers
headers = {}
headers['key'] = 'value'


## 构造request
request = urllib2.Request(url, data=data, headers=headers)

## 准备cookie，安装全局cookie
cookie  = cookielib.CookieJar()
handler = urllib2.HTTPCookieProcessor(cookie)
opener  = urllib2.build_opener(handler)
urllib2.install_opener(opener)


## 发送请求
# response = urllib2.urlopen(request)


'''
cookie也可以通过其他方式获得，如在浏览器登录，从浏览器获得
method 1: 从浏览器中获得，且直接放入headers中
	request.add_header(key, value)

method 2: 构建cookie，从浏览器中复制到一个文件中，然后添加到cookiejar中
	cookie_filename = ''
	cookie  = cookielib.MozillaCookieJar()
	cookie.load(cookie_filename, ignore_discard=True, ignore_expires=True)
	handler = urllib2.HTTPCookieProcessor(cookie)
	opener  = urllib2.build_opener(handler)

	opener.open(request)
'''

def _build_cookie_file(root_url):
	'''向一个站点首页发送GET请求，获得cookie
	并写入一个文件
	'''
	filename = 'newcookie.txt'
	#声明一个MozillaCookieJar对象实例来保存cookie，之后写入文件
	cookie = cookielib.MozillaCookieJar(filename)
	#利用urllib2库的HTTPCookieProcessor对象来创建cookie处理器
	handler = urllib2.HTTPCookieProcessor(cookie)
	#通过handler来构建opener
	opener = urllib2.build_opener(handler)
	#创建一个请求，原理同urllib2的urlopen
	response = opener.open(root_url)
	#保存cookie到文件
	cookie.save(ignore_discard=True, ignore_expires=True)

	return filename


def crawler_xupt():
	'''先在浏览器登录XUPT的首页，从浏览器中复制出cookie，写入文件
	再从文件加载cookie，然后发送POST请求
	'''
	## 准备request

	# 1. url
	url = 'http://222.24.62.120/'

	# 2. data
	values={}
	values['txtUserName']  = os.getenv(username)
	values['TextBox2']     = os.getenv(password)
	values['txtSecretCode']= raw_input('请输入验证码： ')
	data = urllib.urlencode(values)

	# 3. headers
	headers = {}
	headers["Accept"]          = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
	headers["Accept-Encoding"] = "deflate, sdch"
	headers["Accept-Language"] = "zh-CN,zh;q=0.8"
	headers["Cache-Control"]   = "max-age=0"
	headers["Connection"]      = "keep-alive"
	headers["Host"]            = "cuiqingcai.com"
	headers["Upgrade-Insecure-Requests"] = "1"
	headers["User-Agent"]      = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"


	## 构建request
	request = urllib2.Request(url, data=data, headers=headers)


	## 准备cookie
	## 保存cookie的文件对格式有要求
	cookie_filename = 'cookie.txt'
	cookie = cookielib.MozillaCookieJar()
	cookie.load(cookie_filename, ignore_discard=True, ignore_expires=True)
	handler = urllib2.HTTPCookieProcessor(cookie)
	opener = urllib2.build_opener(handler)


	## 发送请求
	response = opener.open(request)
	with open('tmp.html', 'w') as f:
		f.write(response.read())

if __name__ == '__main__':
	# crawler_xupt()
	build_cookie_file()


'''
urllib2库的POST请求使用方法：
1. 构造一个request
	url
	data
	headers

2. 读取cookie文件，并创建一个opener对象
	cookie存放文件格式必须符合一定格式

3. 使用opener对象的open方法发送一个request请求
'''