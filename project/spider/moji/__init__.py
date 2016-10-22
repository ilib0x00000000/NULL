#!/usr/bin/env  python
# -*- coding:utf-8 -*-


'''
爬取墨迹天气的数据
http://tianqi.moji.com/pm/china------------有31个省市的pm数据
'''


import re
import csv
import time
import mailto
import logging
import requests
import multiprocessing


HOST = 'http://tianqi.moji.com/pm/china'

# 日志配置
logging.basicConfig(level=logging.ERROR, format='%(asctime)s %(filename)s [line: %(lineno)d] %(message)s',
	datefmt='%a, %d %b %Y %H:%M:%s', filename='moji.log', filemode='w')


# 1. 构建一个完整的list
def build_urls(root):
	'''主要构建两个数据结构
	1. 所有省份的集合
	2. 省份与地区的映射
	'''
	provinces_lists = []
	cities_maps = {}

	try:
		prov_page = requests.get(root)
		if prov_page.status_code != 200:
			prov_page = requests.get(root)

		if prov_page.status_code != 200:
			logging.error('获取省列表的页面失败')
			return None, None

		# 获取省列表页面成功
		prov_regex_pattern = r'<a href="/pm/china/(.+)">.+</a>'
		prov_regex = re.compile(prov_regex_pattern)

		# 提取出所有省对应的url
		provinces_lists = prov_regex.findall(prov_page.text)
		if provinces_lists:
			for prov in provinces_lists:
				cities_maps[prov] = []

				# 构建每个省的地区的映射
				url = '/'.join([HOST, prov])
				resp = requests.get(url)
				if resp.status_code != 200:
					resp = requests.get(url) 		# 重新发送

				if resp.status_code == 200:
					# 使用正则表达式提取出每个省的地区的页面url
					city_regex_pattern = r'href="(%s/.+)">.+' % url
					city_regex = re.compile(city_regex_pattern, re.UNICODE)

					areaurls = city_regex.findall(resp.text)
					for item in areaurls:
						city = item.split('/')[-2]
						cities_maps[city].append(item)    # 省对应的区域的url映射
				else:
					# 写进日志提醒在获取省的市区列表时error
					logging.error('在获取%s省的市区列表页面时发生错误' % prov)
	except Exception as e:
		# 启动时
		print '获取urls失败.....'
		print 'error: ', e
		print '请重启程序，且检查网络正常.....'
		return None, None
	else:
		print '获取urls成功......'
		print '即将爬取页面数据.......'
		return provinces_lists,cities_maps


# 2. 使用进程池，每个进程去爬一个省
def get_data(proc, city):
	'''每个进程爬取一个省
	proc是省份列表中的
	city是所有省及地区的映射map
	'''
	filename = 'whether_anhui.csv'
	f = open(filename, 'w')
	line = csv.writer(f)

	# while(1):
	urls = city[proc]                                     # 每个进程要爬的url列表
	for url in urls:
		# print url
		resp = requests.get(url)
		if resp.status_code != 200:
			resp = requests.get(url)
			if resp.status_code != 200:
				logging.error('error: 爬取%s出错， 状态码:%d' % (url, resp.status_code))
				continue

		# 处理返回的文本
		pattern = r'<ul class="clearfix">(.+)</ul>'   # 所有数据区域对应的正则
		regex = re.compile(pattern, re.UNICODE|re.DOTALL)
		dataarea = regex.search(resp.text)
		if dataarea:
			single = r'<span>(\d+)</span>'            # 在已得到的数据区域中切出对应的数据
			datalists = re.compile(single, re.UNICODE).findall(dataarea.group(0))
			# [PM10, PM2.5, NO2, SO2, O3, CO]
			tl = time.localtime()
			now = '%d-%02d-%02d %02d:%02d:%02d' % (tl.tm_year, tl.tm_mon, tl.tm_mday, tl.tm_hour, tl.tm_min, tl.tm_sec)
			datalists.insert(0, now)
			# print datalists
			line.writerow(datalists)
		# sleep(60*2)    # 每隔2分钟爬一次

	f.close()
'''
创建进程池：
	Pool(processes=None, initializer=None, initargs=(), maxtasksperchild=None)
		processes: 表示进程的个数
		initializer: 表示工作进程start时调用的初始化函数
		initargs: 表示initializer函数的参数，如果initializer不为None，在每个工作进程start之前会调用initializer(*initargs)

	进程池的一些数据结构：
		self._inqueue:    接收任务队列，用于主进程将任务发送给worker进程
		self._outqueue:   发送结果队列，用于worker进程将结果发送给主进程
		self._taskqueue:  同步的任务队列，保存线程池分配给主进程的任务
		self._cache = {}: 任务缓存
		self._processes:  worker进程个数
		self._pool = []:  worker进程队列
'''



if __name__ == '__main__':
	provinces, city = build_urls(HOST)

	get_data('anhui', city)

	# if provinces and city:
	# 	pool = multiprocessing.Pool(processes = 31)
	# 	for item in provinces:
	# 		pool.apply_async(get_data, (item, city))

	# 	pool.close()
	# 	pool.join()		
	# else:
	# 	print provinces or '省份列表爬取错误'
	# 	print city or '地区urls列表错误'



'''
正则表达式中的点可以匹配除换行符之外的所有字符
如果要点可以匹配换行符，需要指定标志re.DOTALL
'''

