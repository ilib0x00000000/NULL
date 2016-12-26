# -*- coding:utf-8 -*-

import redis

# 创建连接池
pool = redis.ConnectionPool(host='192.168.1.112', port=6379, db=0)

# 创建数据库连接
rd = redis.StrictRedis(connection_pool=pool)

# string API
# set(name, value, ex=None, px=None, nx=False, xx=False)   在redis中设置值，默认，不存在则创建，存在则修改
rd.set('a', 'a的值')

# setnx(name, value)  设置值，只有name不存在时，才执行设置操作
rd.setnx('a', 'a对应的新的值')

# setex(name, time, value) 设置值，过了指定的时间（秒），对应的值就变成None
rd.setex('b', 10, 'value b')

# psetex(name, time_ms, value) 设置值，过了指定的时间（毫秒），对应的值就变成None
rd.psetex('c', 10000, 'value c')

# mset(*arg, **kwargs)    批量设置值
rd.mset({'d':'value d', 'e':'value e'})

# mget(keys, *args)      批量获取
print rd.mget(['a', 'b', 'c', 'd', 'e'])

# getset(name, value)    设置新值并获取原来的值
old_a = rd.getset('a', 'new value of a')
print old_a
print rd.get('a')

# getrange(key, start, end)  获取子序列
print rd.getrange('a', 3, 8)

# setrange(name, offset, value)   修改字符串内容，从指定字符串索引开始向后替换，若新值太大时，则向后添加
rd.setrange('a', 3, ' hello world')

# setbit(name, offset, value)    对name对应的值的二进制表示的位进行操作
# getbit(name, offset)   获取name对应的值的二进制表示中的某位的值（0或1）
# bitcount(key, start=None, end=None)  获取name对应的值得二进制表示中1的个数
# bitop(operation, dest, *keys)   获取多个值，并将值做位运算，将最后的结果保存至新的name对应的值

# strlen(name)     返回name对应的值得字节长度（一个汉字3个字节）
print rd.strlen('a')

# incr(name, amount=1)   自增name对应的值，当name不存在时，则创建name=amount，否则自增
# incrbyfloat(name, amount=1.0)   自增name对应的值，当name不存在时，则创建name=amount，否则自增
# decr(name, amount=1)  自减name对应的值，当name不存在时，则创建name=amount，否则自减
# append(key, value)   在redis name对应的值后面追加内容
