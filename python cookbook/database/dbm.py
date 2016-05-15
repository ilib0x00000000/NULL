#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
anydbm:		面向DBM数据库的前端
whichdb:	anydbm使用whichdb标识数据库

数据库类型：
	dbhash:		anydbm主要后端
	gdbm:		
	dbm:
	dumbdbm:
"""

import anydbm
import whichdb



"""
使用anydbm模块建立数据库
	'c': 创建一个新的数据库
	'n': 创建一个新的数据库而覆盖现有的文件

向数据库中写入数据时：
	键必须是字符串
	值必须是字符串或None
"""
db = anydbm.open('example.db', 'n')

db['key'] = 'value'
db['today'] = 'Sunday'
db['author'] = 'ilib0x00000000'

db.close()

# 查看数据库的类型
# whichdb会报告所创建的数据库的类型
print whichdb.whichdb('example.db')


"""
打开一个数据库
	只读： 'r'
	读写： 'w'
"""

db = anydbm.open('example.db', 'r')

try:
	print 'keys(): ', db.keys()
	for k,v in db.iteritems():
		print k,v
finally:
	db.close()
