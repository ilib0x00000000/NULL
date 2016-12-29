# -*- coding:utf-8 -*-

"""Python操作Redis数据库-list API
"""

import redis


# 创建连接池
pool = redis.ConnectionPool(host='localhost', port=6379, db=0)

# 创建数据库连接
rd = redis.StrictRedis(connection_pool=pool)


# lpush(name, values)
# 在name对应的list中添加元素，每个新的元素都添加到列表的最左边
rd.lpush('redis_list', 'a', 'b', 'c')
# 保存顺序为 'c' 'b' 'a'
print rd.lrange('redis_list', 0, 2)


# lpushx(name, value)
# 在name对应的list中添加元素，只有name已经存在时，值添加到列表的最左边
rd.lpushx('redis_list', 'd')
print rd.lrange('redis_list', 0, 3)


# llen(name)
# 返回name对应的列表元素的个数
print rd.llen('redis_list')


# linsert(name, where, refvalue, value)
# 在name对应的列表中的某一个值得前或后插入一个新值
# where: BEFORE或AFTER
# refvalue: 标杆值，即在它的前或后插入数据
rd.linsert('redis_list', 'BEFORE', 'd', 'e')
print rd.lrange('redis_list', 0, 4)


# lset(name, index, value)
# 在name对应的列表中的某一个索引位置重新赋值
rd.lset('redis_list', 4, 'aaaaaaaa')
print rd.lrange('redis_list', 0, 4)


# lrem(name, value, num)
# 在name对应的list中删除指定的值
# num=0：删除列表中所有指定的值
# num=n：从前向后，删除n个
# num=-n：从后向前，删除n个
rd.lrem('redis_list', 'b', 0)


# lpop(name)
# 删除name对应的列表的左侧获取的第一个元素并删除，返回则是第一个元素
left_first = rd.lpop('redis_list')
print '左边的第一个元素：%s 被删除' % left_first


# lindex(name, index)
# 在name对应的列表中根据索引获取列表元素
print rd.lindex('redis_list', 3)
print rd.lindex('redis_list', 4)


# ltrim(name, start, end)
# 在name对应的列表中移除没有在start-end索引之间的值
last = rd.llen('redis_list')-1
print rd.lrange('redis_list', 0, last)

rd.ltrim('redis_list', 0, 4)

last = rd.llen('redis_list')-1
print rd.lrange('redis_list', 0, last)


# lrange(name, start, end)
# 在name对应的列表分片获取数据


# rpoplpush(src, dst)
# 从一个列表取出最右边的元素，同时将其添加至另一个列表的最左边


# blpop(keys, timeout)
# 将多个列表排列， 按照从左到右去pop对应列表的元素


# brpoplpush(src, dst, timeout=0)
# 从一个列表的右侧移除一个元素并将其添加到另一个列表的左侧
# timeout，当src对应的列表中没有数据时，阻塞等待其有数据的超时时间