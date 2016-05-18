#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-18 21:38:02 
# @Author  : ilib0x00000000
# @email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
csv:以逗号为分隔符的文件（UTF-8编码）
	reader():读取一个文件对象（流），返回一个可迭代对象
	writer():读取文件，返回一个可写对象
		writerow():参数是元组，将元组数据写入文件

当文件不是以逗号为分隔符或者引号需要特别处理，则需要注册方言
	register_dialect(dialect_name, attr=value...)

	再解析该文件时：
	reader(f, dialect=dialect_name)
"""

import csv

# 读取csv文件
with open('test.csv', 'rt') as f:
	rd = csv.reader(f)

	for row in rd:
		print row


# 写入csv文件
with open('test.csv', 'a+b') as f:
	wt = csv.writer(f)

	wt.writerow((6, 'x', '20/05/2016')) 


print '写入数据后'
with open('test.csv', 'rt') as f:
	rd = csv.reader(f)

	for row in rd:
		print row







# 当文件不以逗号为分隔符时，或者解析文件需要指定特殊条件，则应该注册一个方言
csv.register_dialect('pipes', delimiter='|')		# 方言名， 分隔符


with open('test.pipe', 'rb') as f:
	rd = csv.reader(f, dialect = 'pipes')			# 指定方言名

	for row in rd:
		print row








"""
基于字典的阅读器和书写器：
	DictReader():与基于列表的阅读器没什么不同，只是行以字典的形式返回，字典的键为首行的字段名或指定
	
	DictWriter():向文件中写入行时，写入的数据都要是字典
		写入首行:{key1:key1, key2:key2....}
		写入数据:{key1:value1, key2:value2....}
"""
print '基于字典阅读器'
with open('test.csv', 'rb') as f:
	rd = csv.DictReader(f)

	for row in rd:
		print row



with open('test.csv', 'w+b') as f:
	field_names = ('id', 'char', 'date')
	wt = csv.DictWriter(f, fieldnames = field_names)

	# 写入首行
	wt.writerow({'id':field_names[0], 'char':field_names[1], 'date':field_names[2]})

	for i in range(3):
		wt.writerow(
			{
				'id':i,
				'char':chr(ord('a')+i),
				'date':'1%s/05/2016' % str(i)
			}
		)