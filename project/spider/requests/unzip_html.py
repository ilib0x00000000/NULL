#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-05 10:03:47 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
爬取糗事百科的段子，在请求的头部中告诉服务器可以接受压缩网页，则返回的响应的压缩文件
"""

import gzip
import urllib
import urllib2

try:
	from cStringIO import StringIO
except:
	from StringIO import StringIO


url = 'http://www.qiushibaike.com/hot/page/2/'


headers = {}
headers['Host'] = 'www.qiushibaike.com'
headers['User-Agent'] = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:46.0) Gecko/20100101 Firefox/46.0'
headers['Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
headers['Accept-Language'] = 'en-US,en;q=0.5'

# 如果在头部中告诉服务器可以接受压缩，则得到的网页可能是压缩的
headers['Accept-Encoding'] = 'gzip, deflate'


request = urllib2.Request(url, headers=headers)


try:
	response = urllib2.urlopen(request)
	content = response.read()

	# 得到网页的详细信息
	info = response.info()

	# 得到网页的编码
	charset = info.getparam('charset') 

	# 判断网页是否被压缩
	encoding = info.getheader('Content-Encoding')
	
	# 如果网页经过了压缩
	if encoding == 'gzip':
		print '网页经过压缩返回'
		buf = StringIO(content)
		gf = gzip.GzipFile(fileobj=buf)
		content = gf.read()

	print content
except urllib2.URLError, e:
	if hasattr(e, 'code'):
		print 'Error1: '
		print e.code
	if hasattr(e, 'reason'):
		print 'Error2: '
		print e.reason
finally:
	pass