# -*- coding:utf-8 -*-

"""Python操作Redis数据库-hash API
"""

import redis

# 创建连接池
pool = redis.ConnectionPool(host='localhost', port=6379, db=0)


# 创建数据库连接
rd = redis.StrictRedis(connection_pool=pool)

# hset(name, key, value)
# 在name对应的hash中，新增或修改key对应的值
rd.hset('redis_hash', 'a', 'value a')
print rd.hget('redis_hash', 'a')

# hmset(name, mapping)
# 在name对应的hash中批量设置键值对
rd.hmset('redis_hash', {'b':'value b', 'c':'value c', 'd':'value d'})


# hget(name, key)
# 在name对应中hash中根据key获取value
print 'a: %s' % rd.hget('redis_hash', 'a')
print 'b: %s' % rd.hget('redis_hash', 'b')
print 'c: %s' % rd.hget('redis_hash', 'c')
print 'd: %s' % rd.hget('redis_hash', 'd')

# hmget(name, keys, *args)
# 批量获取name对应的hash中多个key对应的值
# 返回值：包含值得列表
print rd.hmget('redis_hash', ['a', 'b', 'c', 'd'])

# hgetall(name)
# 获取name对应hash的所有键值
# 包含所有键值对的字典
print rd.hgetall('redis_hash')


# hlen(name)
# 得到所有键值对的格式hash长度
print rd.hlen('redis_hash')


# hkeys(name)
# 得到所有的keys（类似字典的取出所有keys）
# 包含所有键的列表
print rd.hkeys('redis_hash')


# hvals(name)
# 得到所有的values（类似字典取出所有的value）
# 包含所有值得列表
print rd.hvals('redis_hash')


# hexists(name, key)
# 判断name对应的hash中是否存在当前传入的key
print rd.hexists('redis_hash', 'a')
print rd.hexists('redis_hash', 'e')


# hdel(name, *keys)
# 删除键值对
rd.hdel('redis_hash', 'a')
print rd.hget('redis_hash', 'a')


# hincrby(name, key, amount=1)
# 自增name对应的hash中指定key的值，不存在则创建key=amount
rd.hincrby('redis_hash', 'i', amount=10)
print rd.hget('redis_hash', 'i')
rd.hincrby('redis_hash', 'i', amount=1)
print rd.hget('redis_hash', 'i')


# hincrbyfloat(name, key, amount=1.0)
# 自增自减浮点数
# 自增name对应的hash中指定key的值，不存在则创建key=amount
rd.hincrbyfloat('redis_hash', 'z', amount=1.234)
print rd.hget('redis_hash', 'z')
rd.hincrbyfloat('redis_hash', 'z', amount=1.234)
print rd.hget('redis_hash', 'z')


# hscan(name, cursor=0, match=None, count=None)
# 增量式迭代获取，对于数据大的数据非常有用，hscan可以实现分片的获取数据，并非一次性将数据全部获取完 
# 高能预警
# redis-py: 2.8.0
# redis-server: 2.8.4
# 调用出错！！！！



# hscan_iter(name, match=None, count=None)
# 利用yield封装hscan创建生成器，实现分批去redis中获取数据
# 高能预警
# redis-py: 2.8.0
# redis-server: 2.8.4
# 调用出错！！！！