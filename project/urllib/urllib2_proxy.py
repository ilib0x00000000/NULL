#!/usr/bin/env  python
# -*- coding:utf-8 -*-


'''
urllib2库的使用：
使用代理服务器爬取站点数据
国内高匿代理地址列表：http://www.xicidaili.com/nn/4

获得代理IP和PORT之后
需要发送一个请求到：http://ip.chinaz.com/getip.aspx
验证代理是否可用

参考：
http://www.tuicool.com/articles/F3YRB3N
'''

import re
import sys
import Queue
import socket
import urllib
import urllib2
import threading


try:
	reload(sys)
	sys.setdefaultencoding('utf-8')
except:
	print "Warning: can't set default encoding utf-8"

pattern = r'<tr class="(odd)?">(.*?)</tr>'
regex = re.compile(pattern, re.UNICODE|re.DOTALL)

pattern1 = r'<td>(\d+\.\d+\.\d+\.\d+)|(\d+)</td>'
regex1 = re.compile(pattern1, re.UNICODE|re.DOTALL)

## 1. 获取代理列表
def get_proxy_list(page, queue):
	'''从给定的url获得代理的列表，并写入队列
	参数：
		page:  构造url
		queue: 存放代理信息的队列
	'''
	# 构造request
	url = 'http://www.xicidaili.com/nn/%d' % page
	headers = {}
	headers['User-Agent'] = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"
	request = urllib2.Request(url, headers=headers)

	# 发送请求
	try:
		response = urllib2.urlopen(request)
	except urllib2.HTTPError as httpe:
		print 'HTTP Error: %s' % httpe.code
	except urllib2.URLError as urle:
		print 'URL Error: %s' % urle.reason
	else:
		# 解析页面找到代理信息
		text = response.read()
		_queue_add_lists(text, queue)


def _queue_add_lists(text, queue):
	'''从获得的网页中解析出代理的IP和端口，并写入队列
	参数：
		text:  页面文本
		queue: 存放代理信息的队列
	'''
	lists = regex.findall(text)

	for item in lists:
		data = regex1.findall(item[1])
		queue.put([data[0][0], data[1][1]])

## 2. 测试代理是否可用
def test_proxy(ip, port):
	'''测试获得的代理信息队列中的代理是否可用
	参数：
		ip:   代理的IP
		port: 代理的端口
	'''
	# 构造request
	values = {}
	values['jdfwkey'] = 'asmc1'
	data = urllib.urlencode(values)
	
	headers = {}
	headers["Accept"]          = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
	headers["Accept-Encoding"] = "deflate, sdch"
	headers["Accept-Language"] = "zh-CN,zh;q=0.8"
	headers["Cache-Control"]   = "max-age=0"
	headers["Connection"]      = "keep-alive"
	headers["Host"]            = "cuiqingcai.com"
	headers["Upgrade-Insecure-Requests"] = "1"
	headers["User-Agent"]      = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"

	url = 'http://ip.chinaz.com/getip.aspx?%s' % data

	request = urllib2.Request(url, headers=headers)

	#**********************************************************设置代理***********************************************************#
	proxy = {'http': '%s:%s' % (ip, port)}
	proxy_handler = urllib2.ProxyHandler(proxy)
	opener = urllib2.build_opener(proxy_handler)
	urllib2.install_opener(opener)
	#*****************************************************************************************************************************#

	try:
		response = urllib2.urlopen(request, timeout=30)
	except urllib2.HTTPError as httpe:
		print 'HTTP Error: %s' % httpe.code
	except urllib2.URLError as urle:
		print 'URL Error: %s' % urle.reason
	except Exception:
		print 'else error...'
	else:
		print 'http://%s:%s 可用' % (ip, port) 


if __name__ == '__main__':
	'''准备两个线程池：一个线程池中的线程去爬代理列表的网页，解析后加入队列
	另一个线程池测试爬到的代理是否可用
	'''
	queue = Queue.Queue()

	threads = []
	for i in xrange(1, 6):
		thread = threading.Thread(target=get_proxy_list, args=(i,queue))
		thread.daemon = True
		threads.append(thread)

	for thread in threads:
		thread.start()

	for thread in threads:
		thread.join()

	# print queue.qsize()
	
	threads = []
	while not queue.empty():
		ip, port = queue.get()
		thread = threading.Thread(target=test_proxy, args=(ip, port))
		threads.append(thread)
		thread.daemon = True

	for thread in threads:
		thread.start()

	for thread in threads:
		thread.join()