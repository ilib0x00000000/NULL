Redis-set
**********************

## SADD key member1 [member2]
向集合中添加一个或多个成员
返回值：被添加到集合中的新元素的数量，不包括被忽略的元素
redis> SADD redis-set "hello"
1
redis> SADD redis-set "world"
1
redis> SADD redis-set "hello"
0
redis> SMEMBERS redis-set
1) "hello"
2) "world"


## SCARD key
获取集合的成员数，当key不存在时返回0
redis> SADD redis-set "hello"
redis> SADD redis-set "world"
redis> SADD redis-set "hello"
redis> SCARD redis-set
2


## SDIFF key1 [key2]
返回给定所有集合的差集
redis> SADD redis-set1 "hello"
redis> SADD redis-set1 "foo"
redis> SADD redis-set2 "hello"
redis> SADD redis-set2 "bar"
redis> SDIFF redis-set1 redis-set2
1) "foo"
2) "bar"


## SDIFFSTORE destination key1 [key2]
返回给定所有集合的差集并存储在destination中
redis> SADD redis-set1 "hello"
redis> SADD redis-set1 "foo"
redis> SADD redis-set2 "hello"
redis> SADD redis-set2 "bar"
redis> SDIFFSTORE redis-set redis-set1 redis-set2
2
redis> SMEMBERS redis-set
1) "foo"
2) "bar"


## SINTER key1 [key2]
返回给定所有集合的交集
redis> SADD redis-set1 "hello"
redis> SADD redis-set1 "world"
redis> SADD redis-set1 "foo"
redis> SADD redis-set2 "hello"
redis> SADD redis-set2 "bar"
redis> SINTER redis-set1 redis-set2
1) "hello"

## SINTERSTORE destination key1 key2 ...
返回所有给定集合的交集并存储在destination中
redis> SADD redis-set1 "hello"
redis> SADD redis-set1 "world"
redis> SADD redis-set1 "foo"
redis> SADD redis-set2 "hello"
redis> SADD redis-set2 "bar"
redis> SINTERSTORE redis-set redis-set1 redis-set2
1
redis> SMEMBERS redis-set redis-set1 redis-set2
1) "hello"


## SISMEMBER key member
判断member元素是否是key集合的成员
如果是集合的成员，返回1，如果不是活着key不存在，返回0
redis> SADD redis-set "hello"
redis> SADD redis-set "world"
redis> SISMEMBER redis-set "hello"
1
redis> SISMEMBER redis-set "foo"
0


## SMEMBERS key
返回集合中的所有成员
redis> SADD redis-set "hello"
redis> SADD redis-set "world"
redis> SADD redis-set "foo"
redis> SADD redis-set "bar"
redis> SMEMBERS redis-set
1) "hello"
2) "world"
3) "foo"
4) "bar"


## SMOVE source destination member
将member元素从source集合移动到destination中
redis> SADD redis-set1 "hello"
redis> SADD redis-set1 "world"
redis> SADD redis-set1 "foo"
redis> SADD redis-set2 "bar"
redis> SMOVE redis-set1 redis-set2 "foo"
redis> SMEMBERS redis-set1
1) "hello"
2) "world"
redis> SMEMBERS redis-set2
1) "foo"
2) "bar"


## SPOP key
移除并返回集合中的一个随机元素，当集合不存在或者是空集时，返回nil
redis> SADD redis-set "hello"
redis> SADD redis-set "world"
redis> SADD redis-set "foo"
redis> SPOP redis-set
"world"
redis> SMEMBERS redis-set
1) "hello"
2) "foo"


## SRANDMEMBER key [count]
返回集合中一个或多个随机数
只提供集合key参数时，返回一个元素
如果集合为空，返回nil
如果提供了count参数，那么返回一个数组
如果集合为空，返回空数组
redis> SADD redis-set "hello"
redis> SADD redis-set "world"
redis> SADD redis-set "bar"
redis> SADD redis-set "foo"
redis> SRANDMEMBER redis-set 2
1) "hello"
2) "world"


## SREM key member1 [member2...]
移除集合中一个或多个成员
返回被成功移除的元素的数量，不包括被忽略的元素
redis> SADD redis-set "hello"
redis> SADD redis-set "world"
redis> SADD redis-set "foo"
redis> SADD redis-set "bar"
redis> SREM redis-set "hello" "world"
2
redis> SREM redis-set "hello" "world"
0


## SUNION key1 [key2...]
返回所有集合的并集
redis> SADD redis-set1 "hello"
redis> SADD redis-set1 "world"
redis> SADD redis-set1 "foo"
redis> SADD redis-set2 "hello"
redis> SADD redis-set2 "bar"
redis> SUNION redis-set1 redis-set2
1) "hello"
2) "world"
3) "foo"
4) "bar"


## SUNIONSTORE destination key1 key2 ...
返回给定集合的并集，并存放到指定集合destination中
redis> SADD redis-set1 "hello"
redis> SADD redis-set1 "world"
redis> SADD redis-set1 "foo"
redis> SADD redis-set2 "hello"
redis> SADD redis-set2 "bar"
redis> SUNION redis-set redis-set1 redis-set2
redis> SMEMBERS redis-set
1) "hello"
2) "world"
3) "foo"
4) "bar"


## SSCAN key cursor [MATCH pattern][COUNT count]
迭代集合中的元素