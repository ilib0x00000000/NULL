#!/usr/bin/env  python
# -*- coding:utf-8 -*-


'''
爬取墨迹天气的数据
http://tianqi.moji.com/pm/china------------有31个省市的pm数据
'''


import re
import requests
import multiprocessing


HOST = 'http://tianqi.moji.com/pm/china'


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
		prov_regex_pattern = r'<a href="/pm/china/(.+)">.+</a>'
		prov_regex = re.compile(prov_regex_pattern)

		# 提取出所有省对应的url
		provs = prov_regex.findall(prov_page.text)
		if provs:
			for item in provs:
				provinces_lists.append('/'.join([HOST, item]))
				cities_maps[item] = []

			# 构建每个省的地区的映射
			for url in provinces_lists:
				resp = requests.get(url)
				if resp.status_code != 200:
					resp = requests.get(url) 		# 重新发送

				# 使用正则表达式提取出每个省的地区的页面url
				city_regex_pattern = r'href="(%s/.+)">.+' % url
				city_regex = re.compile(city_regex_pattern, re.UNICODE)

				areaurls = city_regex.findall(resp.text)
				for item in areaurls:
					city = item.split('/')[-2]
					cities_maps[city].append(item)
	except:
		# 发送邮箱提醒
		print 'error'
		return None, None
	else:
		return provinces_lists,cities_maps


# 2. 使用进程池，每个进程去爬一个省
def get_data(proc, city):
	'''每个进程爬取一个省
	proc是省份列表中的
	city是所有省及地区的映射map
	'''
	# 每个进程要爬的url列表
	urls = city[proc] 
	for url in urls:
		try:
			resp = requests.get(url)
			if resp.status_code != 200:
				resp = requests.get(url)
				if resp.status_code != 200:
					# 写进日志
					return None

			# 处理返回的文本
			pattern = r'<ul class="clearfix">(.+)</ul>'   # 所有数据区域对应的正则
			regex = re.compile(pattern, re.UNICODE)
			dataarea = regex.findall(resp.text)

			single = r'<span>\d+</span>'    # 在已得到的数据区域中切出对应的数据
			datalists = re.compile(single, re.UNICODE).findall(dataarea[0])
			print datalists
		except:
			print 'error'





if __name__ == '__main__':
	provinces, city = build_urls(HOST)

	pool = multiprocessing.Pool(processes = 31)
	for item in provinces:
		pool.apply_async(get_data, (item, city))

	pool.close()
	pool.join()


'''
HOST = 'www.tianqi.moji.com'

url = 'http://tianqi.moji.com/pm/china'
response = requests.get(url)

# 从网页中匹配出每个城市的地址
regex = re.compile(r'<a href="/pm/china/(.+)">.+</a>', re.UNICODE)

provinces = regex.findall(response.text)



# 得到每个省对应的页面，然后从该页面中获取不同的地区的pm数据
for item in provinces:
	securl = '/'.join([url, item])
	print securl
	secresponse = requests.get(securl)

	pattern = r'href="%s/.+">.+' % securl
	print pattern
	nregex = re.compile(pattern, re.UNICODE)
	thrdurls = nregex.findall(secresponse.text)

	for item in thrdurls:
		print item
'''

