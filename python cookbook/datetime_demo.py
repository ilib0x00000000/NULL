#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
与时间有关的标准库：
	o time模块
	o datetime模块
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




def test_datetime():
	"""datetime模块（日期，时间都是类）：
		time类属性：
			o hour:小时
			o minute:分钟
			o second:秒数

		date类：
			属性：
				o year: 年
				o month: 月
				o day: 日

			方法：
				o ctime(): 返回格式化的日期时间字符串
				o today(): 返回今天的日期字符串
				o weekday(): 返回当前日期是一周的第几天
				o timetuple():返回当前日期的结构体

		datetime类：
			属性：包含time和date类的属性
			方法：包含time和date类的方法
	"""
	tm = datetime.time(1, 2, 3)
	print tm.hour, '\t', tm.minute, '\t', tm.second

	dt = datetime.date(2016, 05, 09)
	print dt.year, dt.month, dt.day
	print dt.ctime()
	print dt.today()
	print dt.weekday()
	print dt.timetuple()





if __name__ == '__main__':
	test_time()