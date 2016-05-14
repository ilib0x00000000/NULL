# coding:utf-8

"""
使用SQLAlchemy连接数据库：
	1. 数据库的相关信息保存在系统环境变量中
	2. SQLAlchemy连接数据库是基于数据库的驱动，所以连接时，需要加上数据库驱动名(mysqldb)
"""


import os

# 导入
from sqlalchemy import create_engine, Column, Integer, String
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

mysql_db_user = os.getenv('MYSQL_DB_USER')
mysql_db_passwd = os.getenv('MYSQL_DB_PASSWD')
mysql_db_database = os.getenv('MYSQL_DB_DATABASE')
mysql_db_table = os.getenv('MYSQL_DB_TABLE')




# 创建对象的基类
Base = declarative_base()

# 定义表中数据对象
class User(Base):
	# 表的名字
	__tablename__ = mysql_db_table

	# 表的结构
	pid = Column(Integer, primary_key=True)
	name = Column(String)
	sex = Column(Integer)
	score = Column(Integer)



connect_mysql = 'mysql+mysqldb://' + mysql_db_user +':'+ mysql_db_passwd +'@localhost:3306/' + mysql_db_database  
# 连接数据库，连接方式如下
# 数据库名+数据库连接驱动名://用户:密码@主机名:端口/数据库名
# 'mysql+mysqldb://root:password@localhost:3306/test'
engine = create_engine(connect_mysql)



# 创建程序与数据库之间的对话
Session = sessionmaker(bind=engine)
session = Session()



new_user = User(pid=1035, name='mack', sex=0, score=67)

# 向对话中加入对象
session.add(new_user)


# 提交事物
session.commit()


# 关闭对话
session.close()
