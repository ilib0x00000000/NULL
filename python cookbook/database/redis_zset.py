#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""Python操作Redis数据库-zset API
在集合的基础上，为每个元素排序，元素的排序需要根据另外一个值来进行比较。所以，对于有序集合，每一个元素有两个值。即：值和分数，分数专门用来做排序
"""

import redis

rd = redis.Redis(host='localhost', port=6379, db=0)

# zadd(name, *args, **kwargs)
# 向name对应的有序集合中添加元素
rd.zadd('redis_zset', 'a', 1, 'b', 2)   # 向redis_zset有序集合中添加分数值为1的元素'a'和分数值为2的元素'b'
rd.zadd('redis_zset', 'c', 3, 'd', 4, 'e', 5, 'f', 5, 'g', 3)

# zcard(name)
# 获取name对应的有序集合元素的数量
print rd.zcard('redis_zset')


# zcount(name, min, max)
# 获取name对应的有序集合中分数在[min, max]之间的个数
print rd.zcount('reids_zset', 1, 3)


# zincrby(name, value, amount)
# 自增name对应的有序集合中value对应的分数
# 返回值：有序集合的元素的分数值加上指定值之后的值
print rd.zincrby('redis_zset', 'a', 5)


# zrange(name, start, end, desc=False, withscores=False, score_cast_func=float)
# 按照索引范围获取name对应的有序集合的元素
# 参数
# name: redis的name
# start: 有序集合索引起始位置（非分数）
# end: 有序集合索引结束位置（非分数）
# desc: 排序规则，默认按照分数从小到大排序
# withscores: 是否获取元素的分数，默认只获取元素的值
# score_cast_func: 对分数进行数据转换的函数
length = rd.zcard('redis_zset')
print rd.zrange('redis_zset', 0, length-1)


# zrank(name, value)
# 获取某个值在name对应的有序集合中的排行
print rd.zrank('redis_zset', 'a')


# zrangebylex(name, min, max, start=None, num=None)
# 当有序集合的所有成员都具有相同的分数值时，有序集合的元素会根据成员的值来排序
# 高能预警！！！！！
# 调用时出错
# print rd.zrangebylex('redis_zset', 0, 10)


# zrem(name, values)
# 删除name对应的有序集合中值是values的成员
rd.zrem('redis_zset', 'a')  # 返回值是删除元素的个数


# zscore(name, values)
# 获取name对应的有序集合中values对应的分数
print rd.zscore('redis_zset', 'b')


# zremrangebyrank(name, min, max)
# 根据排行范围删除


# zremrangebyscore(name, min, max)
# 根据分数范围删除

# zremrangelex(name, min, max)
# 根据值返回删除

# zinterstore(dest, keys, aggregate=None)
# zunionstore(dest, keys, aggregate=None)

# zscan(name, cursor=0, match=None, count=None, score_cast_func=float)
# zscan_iter(name, match=None, count=None, score_cast_func=float)