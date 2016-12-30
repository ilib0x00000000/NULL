# -*- coding:utf-8 -*-

"""Python操作Redis数据库-set API
set集合不允许重复的列表
"""

import redis

rd = redis.Redis(host='localhost', port=6379, db=0)

# sadd(name, value)
# 向集合中添加元素
# 返回值：若成功添加，返回添加到集合中的元素的个数
rd.sadd('redis_set', '1')
rd.sadd('redis_set', '2', '3', '4')
rd.sadd('redis_set', 'a', 'b', 'c')


# scard(name)
# 获取name对应集合中元素个数
print rd.scard('redis_set')


# smembers(name)
# 获取集合name中的全部元素
print rd.smembers('redis_set')

# smove(src, dst, value)
# 将某个成员从一个集合中移动到另一个集合中


# spop(name)
# 从集合的右侧（尾部）移除一个成员，并将其返回
obj = rd.spop('redis_set')
print obj


# srandmember(name, numbers)
# 从name对应的集合中随机获取numbers个元素
objs = rd.srandmember('redis_set', 4)
print objs


# srem(name, values)
# 在name对应的集合中删除某些值
# 返回值：若成功，返回删除元素的个数，若失败，返回0
rd.srem('redis_set', 'a')


# sismember(name, value)
# 判断value是否存在指定的name集合中
rst = rd.sismember('redis_set', 'a')
print rst
rst = rd.sismember('redis_set', 'b')
print rst



# sinter(keys, *args)
# 返回多个集合的交集
s1 = rd.sadd('redis_set1', 'a', 'b', '0')
s2 = rd.sadd('redis_set2', '1', '2', '0')
inter = rd.sinter('redis_set1', 'redis_set2')
print inter


# sinterstore(dest, keys, *args)
# 获取多个集合的交集，再将结果存放到指定集合中
# 返回值：返回交集的个数
print rd.sinterstore('inter', 'redis_set1', 'redis_set2')
print rd.smembers('inter')


# sunion(keys, *args)
# 获取多个name对应的集合的并集
# 返回值：集合的并集
union = rd.sunion('redis_set1', 'redis_set2')
print union


# sunionstore(dest, keys, *args)
# 获取多个name对应的集合的并集，并将结果保存到dest对应的集合中
# 返回值：返回并集的元素个数
print rd.sunionstore('union', 'redis_set1', 'redis_set2')
print rd.smembers('union')


# sdiff(keys, *args)
# 在第一个name对应的集合中且不在其他name对应的集合的元素集合
diff = rd.sdiff('redis_set1', 'redis_set2')
print rd.smembers(diff)


# sdiffstore(dest, keys, *args)
# 获取第一个name对应的集合中且不在其他name对应的集合，再将其加入到dest对应的集合中
print rd.sdiffstore('diff', 'redis_set1', 'redis_set2')
print rd.smembers('diff')
