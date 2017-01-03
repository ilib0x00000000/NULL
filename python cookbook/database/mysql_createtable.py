#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""Python连接MySQL
创建两张表，一张学生信息表，一张成绩表。学生信息表的主键对应成绩表的外键

学生信息表字段： sid（学号），name（学生姓名），sex（性别），birth（出生日期），major（专业）
成绩表字段：sid（学号），math（数学），english（英语），chinese（语文）
"""


import MySQLdb

# API connect(host, user, password, database)
mysql_db = MySQLdb.connect('localhost', 'root', 'xxxxx', 'pytest')

table_stuinfo_sql = """
CREATE TABLE stu_info(
	sid INTEGER PRIMARY KEY AUTO_INCREMENT,
	name varchar(64) NOT NULL,
	sex INTEGER NOT NULL default 1,
	birth DATE NOT NULL,
	major INTEGER NOT NULL
);
"""

table_recond_sql = """
CREATE TABLE recond(
	rid INTEGER PRIMARY KEY,
	sid INTEGER,
	math INTEGER NOT NULL,
	english INTEGER NOT NULL,
	chinese INTEGER NOT NULL,
	CHECK(math<=100 AND math>=0),
	CHECK(english<=100 AND english>=0),
	CHECK(chinese<=100 AND chinese>=0),
	FOREIGN KEY(sid) REFERENCES stu_info(sid)
);
"""

# 创建游标：cursor
cursor = mysql_db.cursor()

try:
	cursor.execute(table_recond_sql)
	cursor.execute(table_stuinfo_sql)
except MySQLdb.Warning as warn:
	print 'warn: 创建数据库表失败'
	print warn
except MySQLdb.Error as error:
	print 'error: 创建数据库表失败'
	print error
except MySQLdb.DatabaseError as dberror:
	print 'DatabaseError: 创建数据库表失败'
	print dberror
except Exception:
	print 'Exception: 创建数据库表失败'


# 关闭数据库连接
mysql_db.close()