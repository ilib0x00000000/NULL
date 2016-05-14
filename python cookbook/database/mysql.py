#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
ubuntu14.04下安装MySQL驱动:
	1. apt-get install python-dev
	2. apt-get install libmysqlclient-dev
	3. pip install mysql-python

设置系统环境变量：
	export MYSQL_DB_USER=*
	export MYSQL_DB_PASSWD=*
	export MYSQL_DB_DATABASE=*
	export MYSQL_DB_TABLE=*


数据库连接：
	connect(host, user, passwd, db)


连接对象方法：
	close()
	commit()
	rollback()
	cursor()
	errorhandler(cxn, cur, errcls, errval)

游标对象属性：
	arraysize
	connection
	description
	lastrowid
	rowcount
	close()
	execute(op [,args])
	executemany(op, args)
	fetchone()
	fetchmany([size = cursor.arraysize])
	fetchall()


读取系统环境变量：
	os.getenv()
"""

import os
import sys
import MySQLdb

try:
	reload(sys)
	sys.setdefaultencoding('utf-8')
except:
	pass


mysql_db_user = os.getenv('MYSQL_DB_USER')
mysql_db_passwd = os.getenv('MYSQL_DB_PASSWD')
mysql_db_database = os.getenv('MYSQL_DB_DATABASE')
mysql_db_table = os.getenv('MYSQL_DB_TABLE')


# 连接数据库，得到连接对象
conn = MySQLdb.connect( host="localhost", 
						user=mysql_db_user, 
						passwd=mysql_db_passwd, 
						db=mysql_db_database)

cursor = conn.cursor() 
cursor.execute("select * from "+mysql_db_table)
res = cursor.fetchall()		# 返回对象是一个元组

print res


cursor.close() 
conn.close()
