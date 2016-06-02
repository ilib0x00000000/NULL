#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-02 16:38:22 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
requests库的简单使用-Response对象
官方文档API：http://cn.python-requests.org/zh_CN/latest/api.html#requests.Response
"""

import requests

'''
Response对象
		headers = None:			http响应的头部
		content:				网页的内容
		encoding = None:		网页的编码	
		status_code = None:		http请求返回的状态码
		cookies = None:			cookie
		url = None:				当前网页的url

		elapsed = None:			
		history = None
		iter_content(chunk_size=1, decode_unicode=False)
		iter_lines(chunk_size=512, decode_unicode=None)
		json(**kwargs)
		apparent_encoding:		
		links
		raise_for_status()
		raw = None
		text:					对网页做了编码处理，对响应对象的text使用与网页的相同编码处理，得到的内容与content相同，尽量避免使用text
'''




try:
	resp = requests.get('http://www.baidu.com')

	if resp.status_code == 200:
		print 'get page...'

		print '\theader: ', resp.headers
		print '\tencoding: ', resp.encoding
		print '\tstatus_code:', resp.status_code
		print '\turl: ', resp.url
		print '---' * 20
		# parse(resp.content)
		
		# 分解headers,CaseInsensitiveDict对象
		for key in resp.headers:
			print key,' : ', resp.headers[key]

		print '---' * 20
		print '\tcookies: ', resp.cookies
	else:
		print resp.status_code
except:
	print 'net error'