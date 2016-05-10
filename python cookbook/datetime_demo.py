#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
与时间有关的标准库：
	o time模块
	o datetime模块

常用的函数：
	1.获得当前时间戳
		time.time()
		
	2.获得当前格式化日期时间字符串
		time.ctime()

	3.获得当前日期时间对象
		datetime.datetime.now()

	4.把字符串转换成日期时间对象返回
		datetime.datetime.strptime(date_string, format)
"""

import time
import datetime



def test_time():
	"""time模块:
				时间戳<------------>	格式化时间字符串<------------>时间结构体
						
		o time(): 		返回自纪元以来经过的秒数
		o ctime([time]):如果给定一个秒数，就返回该秒数的格式化时间字符串，否则就返回当前的格式化时间字符串
		o mktime(struct_time):根据给定的时间结构体，返回一个时间戳
		o gmtime():		返回世界标准时
		o localtime():	返回当前时区的时间
		o strptime(string, format):根据所给的字符串和格式返回一个时间结构体
		o strftime(format  [,t]):将时间结构体转换成字符串，默认时间是当前时间
	"""
	print '时间戳：', time.time()
	print '格式化日期时间字符串：', time.ctime()
	print '时间结构体:'
	lt = time.localtime()
	print 'tm_year:', lt.tm_year
	print 'tm_mon:',  lt.tm_mon
	print 'tm_mday:', lt.tm_mday
	print 'tm_hour:', lt.tm_hour
	print 'tm_min:',  lt.tm_min
	print 'tm_sec:',  lt.tm_sec


	print '\n\n'
	print '时间之间的转换'
	print '时间结构体------>时间戳:', time.mktime(time.localtime())

	print '字符串时间------>时间结构体:', time.strptime('2016-05-09 22:25:18', '%Y-%m-%d %H:%M:%S')
	print '时间结构体------>字符串时间:', time.strftime('%Y-%m-%d %H:%M:%S')
	print 



def test_date():
	"""datetime模块中的date类
			属性：
				o year: 年
				o month: 月
				o day: 日

			方法：
				o ctime(): 返回格式化的日期时间字符串
				o weekday(): 返回当前日期是一周的第几天
				o timetuple():返回当前日期的结构体

			类方法：
				o today(): 返回今天的日期字符串
				o fromtimestamp(): 把时间戳转换成日期
	"""
	ts = time.time()
	print datetime.date.fromtimestamp(ts)


	# 日期对象的运算
	# 1.创建一个timedelta对象
	tdl = datetime.timedelta(days = 1)
	today = datetime.date.today()
	print today

	# 2.运算
	yesterday = today - tdl
	tomorrow = today + tdl
	print 'yesterday: ', yesterday
	print 'tomorrow: ', tomorrow
	print 


def test_datetime():
	"""datetime模块（日期，时间都是类）：
		time类属性：
			o hour:小时
			o minute:分钟
			o second:秒数

		datetime类：
			属性：包含time和date类的属性
			方法：包含time和date类的方法
	"""
	tm = datetime.time(1, 2, 3)
	print tm.hour, '\t', tm.minute, '\t', tm.second


	print datetime.datetime.now()		# 返回现在的日期时间
	print datetime.datetime.today()		# 同上

	# 格式化与解析
	# 1.把日期时间对象转换成字符串
	s = datetime.datetime.today().strftime('%Y-%m-%d %H:%M:%S')
	print s
	print type(s)

	# 2.把字符串转换成日期时间对象
	dt = datetime.datetime.strptime('2015-5-10 21:27:35', '%Y-%m-%d %H:%M:%S')
	print dt
	print type(dt)


if __name__ == '__main__':
	test_time()
	test_date()
	test_datetime()