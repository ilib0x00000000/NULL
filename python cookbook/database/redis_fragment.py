#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""Redis数据库其他常用操作
参考:[http://www.cnblogs.com/wang-yc/articles/5693288.html]
"""

import redis

rd = redis.Redis(host='localhost', port=6379, db=0)

# delete(*name)
# 根据name删除redis中的任意数据

# exists(name)
# 检验数据库中是否存在name
if rd.exists('redis_zset'):
	rd.delete('redis_zset')


# keys(pattern='*')
# 根据模型获取redis的name
print rd.keys(pattern='redis_*')
# ['redis_set2', 'redis_set1', 'redis_hash', 'redis_set', 'redis_zset']


# expire(name, time)
# 为redis的name设置一个过期时间
rd.expire('redis_hash', 1000)  # 返回True表示成功


# rename(src, dst)
# 对redis的name重命名
rd.rename('redis_set', 'new_redis_set')
print rd.keys(pattern='redis_*')


# move(name, db)
# 将redis的某个值移动到指定的db下


# randomkey()
# 随机获取一个redis的name（不删除）
print rd.randomkey()


# type(name)
# 获取name对应的值得类型
print rd.type('redis_hash')
print rd.type('redis_set2')
print rd.type('redis_zset')


# scan(cursor=0, match=None, count=None)
# scan_iter(match=None, count=None)