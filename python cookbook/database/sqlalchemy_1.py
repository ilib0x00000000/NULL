#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""ORM-SQLalchemy

类型名称         Python类型          描述
Integer         int                整型，通常为32位
SmallInteger    int                短整型，通常为16为
BigInteger      int/long           精度不受限整型
Float           float              浮点数
Numeric         decimal.Deciaml    定点数
String          str                可变长度字符串
Text            str                可变长度字符串，适合大量文本
Unicode         unicode            可变长度Unicode字符串
Boolean         bool               布尔型
Date            datetime.date      日期类型
Time            datetime.time      时间类型
Interval        datetime.timedelta 时间间隔
Enum            str                字符列表
PickleType      任意Python对象      自动Pickle序列化
LargeBinary     str                二进制


常见的SQLalchemy选项
可选参数         描述
primary_key     如果设置为True，则为该列表的主键
unique          如果设置为True，则该列不允许相同值
index           如果设置为True，为该列创建索引，查询效率会更高
nullable        如果设置为True，则该列允许为空，否则不允许为空
default         定义该列的默认值
"""

import sys
from sqlalchemy import Column, String, create_engine, Integer, ForeignKey
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

try:
	reload(sys)
	sys.setdefaultencoding('utf-8')
except Exception:
	print 'encoding erro'


DBUSER     = 'root'
DBPASSWORD = 'xxxxxx'
DBIP       = 'localhost'
DBPORT     = '3306'
DBNAME     = 'xxxxxx'

# 创建对象的基类
Base = declarative_base()


# 定义与数据库中表对应的对象
class Stuinfo(Base):
	__tablename__ = 'stu_info'

	sid = Column(Integer, primary_key=True)
	name = Column(String(64))
	sex = Column(Integer)
	birth = Column()
	major = Column(Integer, ForeignKey('majors.mid'))

class Major(Base):
	__tablename__ = 'majors'

	mid = Column(Integer, primary_key=True)
	major_name = Column(String(64))


class Recond(Base):
	__tablename__ = 'recond'

	rid = Column(Integer, primary_key=True)
	sid = Column(Integer, ForeignKey('stu_info.sid'))
	chinese = Column(Integer)
	english = Column(Integer)
	math = Column(Integer)


# 创建数据库连接引擎
# **************************************
# *              高能预警               *
# **************************************
# 为了避免中文乱码，创建连接引擎时要指定字符编码charset=utf8
engine = create_engine('mysql+mysqldb://%s:%s@%s:%s/%s?charset=utf8' % (DBUSER, DBPASSWORD, DBIP, DBPORT, DBNAME))


# 创建Session类
Session  = sessionmaker(bind=engine)
# 创建Session对象
session = Session()


# 使用session对象查询数据
majors = session.query(Major).all()

print('专业代号：专业名称')
for major in majors:
	print('%s  :   %s' % (major.mid, major.major_name.decode('utf-8')))


# 插入
new_major = Major(mid=7236, major_name='软件工程'.encode('utf-8'))
session.add(new_major)

# 提交事务
session.commit()


# 关闭session
session.close()