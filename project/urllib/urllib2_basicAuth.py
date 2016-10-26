#!/usr/bin/env  python
# -*- coding:utf-8 -*-

'''
urllib2库的使用：
基本认证-----basic Authorization
基本认证就是添加一个header头部
键： Authorization
值： username+:+password使用base64编码

在需要使用基本验证的时候，服务端会返回一个错误响应，该响应的头部中Www-authenticate: Basic realm="..." 

HTTP + 基本认证，在传输时不安全，所以在使用基本认证时一般使用HTTPS传输
HTTP + OAuth
HTTP + 摘要认证（digest authentication）
HTTP + WSSE认证（WS-Security）

参考：
http://kb.cnblogs.com/page/158829/
http://www.iteedu.com/plang/python/urllib2/basicauth.php
http://www.th7.cn/Program/Python/201411/314448.shtml
'''

import sys
import urllib2

try:
	reload(sys)
	sys.setdefaultencoding('utf-8')
except:
	print "Warning: can't set default encoding utf-8"


def basicauth_by_header(username, password):
	'''在发送的请求中加一个header
	Authorization: Basic base64.encode(username+':'+password)
	'''
	import base64
	# 构造request
	url = ''
	headers = {}
	auth = base64.b64encode('%s:%s' % (username, password))
	headers['Authorization'] = ' Basic %s' % auth
	request = urllib2.Request(url, headers=headers)

	# 发送请求
	try:
		response = urllib2.urlopen(request)
	except Exception:
		print "Error: Can't send request"


def basicauth_by_handler(url, realm, username, password):
	'''创建一个handler处理基本认证的参数
	realm参数由第一次发送请求时，服务端的响应中的header，例如：Www-authenticate: SCHEME realm="REALM".
	可以从浏览器中获得
	'''
	# 构建request
	headers = {}
	request = urllib2.Request(url, headers=headers)

	#**********************************创建一个基本认证handler**************************************#
	handler = urllib2.HTTPBasicAuthHandler()
	handler.add_password(realm, url, username, password)
	opener = urllib2.build_opener(handler)
	urllib2.install_opener(opener)
	#***********************************************************************************************#

	# 发送请求
	try:
		response = urllib2.urlopen(request)
	except Exception:
		print 'Error: Can\'t send request'


def basicauth_by_defaultrealm(url, username, password):
	'''创建一个Authorization handler，但是使用默认realm，即不需要在浏览器中获取该值
	'''
    # 构造request
    headers = {}

    request = urllib2.Request(url, headers=headers)

	#*****************************创建一个默认的基本认证handler*************************************#
	psmg = urllib2.HTTPPasswordMgrWithDefaultRealm()         
	psmg.add_password(None,url,username,password)        
	handler = urllib2.HTTPBasicAuthHandler(psmg)        
	opener = urllib2.build_opener(handler)        
	urllib2.install_opener(opener)        
	#***********************************************************************************************#

	# 发送request
	try:
		response = urllib2.urlopen(request)
	except Exception:
		print "Error: can't send request"


'''
总结urllib2库使用基本认证的3种方式：
	1. 直接在请求的header头中加入键值对： headers['Authorization'] = ' Basic %s' % auth
	2. 创建一个Authorization Handler，使用服务器返回的realm字段
	3. 创建一个默认的Authorization Handler，可以不使用realm字段
'''