#!/usr/bin/env  python
# -*- coding:utf-8 -*-


'''
urllib2库的使用：
处理发送请求之后出现的异常：
异常有两种-------URLError/HTTPError

URLError
	错误原因：
		* 本地网络错误
		* 服务器不存在
	异常属性：
		reason

HTTPError(URLError的子类)
	错误原因：
		* 30x
		* 40x
		* 50x
	异常属性：
		code
'''

import sys
import urllib
import urllib2

try:
	reload(sys)
	sys.setdefaultencoding('utf-8')
except:
	print "Warning: can't set default encoding utf-8"


def error_handler1(url):
	'''处理urllib2异常的第一种方式
	'''
	headers = {}
	headers['User-Agent'] = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"

	# 构造request
	request = urllib2.Request(url, headers=headers)

	# 发送request
	try:
		response = urllib2.urlopen(request)
	except urllib2.HTTPError as httpe:
		print httpe.code, httpe.reason
	except urllib2.URLError as urle:
		print urle.reason
	except Exception:
		print 'else exception...'
	else:
		print 'No Error'

def error_handler2(url):
	'''处理urllib2异常的第二种方式
	'''
	headers = {}
	headers['User-Agent'] = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"

	# 构造request
	request = urllib2.Request(url, headers=headers)

	# 发送request
	try:
		response = urllib2.urlopen(request)
	except Exception as e:
		if hasattr(e, 'code'):
			print 'HTTP Error: ', e.code
		elif hasattr(e, 'reason'):
			print 'URL Error: ', e.reason
		else:
			print 'Unknown Error'
	else:
		print 'No Error'

if __name__ == '__main__':
	if len(sys.argv)==2:
		error_handler1(sys.argv[1])
		error_handler2(sys.argv[1])
	else:
		print 'Usage: python urllib2_error.py <url>'
