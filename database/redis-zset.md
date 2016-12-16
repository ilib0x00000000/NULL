Redis-zset
****************************************

## ZADD key socre0 member0 [score1 member1]
向有序集合中添加一个或多个成员，或者更新已存在的成员的分数
redis> ZADD redis-zset 1 "hello"
1
redis> ZADD redis-zset 1 "foo"
1
redis> ZADD redis-zset 2 "world" 3 "bar"
2
redis> ZRANGE redis-zset 0 -1 WITHSCORES
1) "hello"
2) 1
3) "foo"
4) 1
5) "world"
6) 2
7) "bar"
8) 3

## ZCARD key
获取有序集合的成员数
redis> ZADD redis-zset 1 "hello"
redis> ZADD redis-zset 1 "world"
redis> ZADD redis-zset 2 "foo" 3 "bar"
redis> ZCARD redis-zset
4

## ZCOUNT key min max
计算在有序集合中指定区间分数的成员数
redis> ZADD redis-zset 1 "hello"
redis> ZADD redis-zset 1 "world"
redis> ZADD redis-zset 2 "foo" 3 "bar"
redis> ZCOUNT redis-zset 1 3
4

## ZINCRBY key increment member
有序集合中对指定成员的分数加上增量increment
可以传递一个负数值，让分数减去相应的值
当key不存在，或者分数不是key的成员时，ZINCRBY等同于ZADD
当key不是有序集合类型时，返回一个错误
redis> ZADD redis-zset 1 "hello"
redis> ZADD redis-zset 1 "foo"
redis> ZINCRBY redis-zset 2 "hello"
3
redis> ZRANGE redis-zset 0 -1 WITHSCORES
1) "foo"
2) "2"
3) "hello"
4) "3"

## ZINTERSTORE destination numkeys key 
计算给定的一个或多个有序集的交集并将结果集存储在新的有序集合key中
交集的分数会累加
// 有序集合1
redis> ZADD redis-zset1 92 "hello"
redis> ZADD redis-zset1 94 "world"
redis> ZADD redis-zset1 48 "foo"
// 有序集合2
redis> ZADD redis-zset2 93 "hello"
redis> ZADD redis-zset2 91 "world"
redis> ZADD redis-zset2 90 "bar"

redis> ZINTERSTORE redis-set 2 redis-set1 redis-set2
redis> ZRANGE redis-set 0 -1 WITHSCORES
1) "hello"
2) 185
3) "world"
4) 185



## ZRANGE key start stop [WITHSCORES]
通过索引区间返回有序集合指定区间内的成员
redis> ZADD redis-set 0 "hello"
redis> ZADD redis-set 1 "world"
redis> ZADD redis-set 2 "foo" 3 "bar"
redis> ZRANGE redis-set 0 3 WITHSCORES
1) "hello"
2) "0"
3) "world"
4) "1"
5) "foo"
6) "2"
7) "bar"
8) "3"



## ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT]
通过分数返回有序集合指定分数区间内的成员
redis> ZADD redis-set 8500 "zhangsan"
redis> ZADD redis-set 6800 "lisi"
redis> ZADD redis-set 10029 "wangwu"
redis> ZRANGEBYSCORE redis-set -inf +inf
1) "zhangsan"
2) "lisi"
3) "wangwu"


## ZRANK key member
返回有序集合中指定成员的索引
redis> ZADD redis-set 3890 "zhangsan"
redis> ZADD redis-set 2050 "lisi"
redis> ZADD redis-set 5000 "wangwu"
redis> ZRANK redis-set "zhangsan"
1

## ZREM key member0 [member1 ...]
移除有序集合中的一个或多个集合


## ZREMRANGEBYSCORE key start stop
移除有序集合中给定排名区间的所有成员
redis> ZREMRANGEBYSCORE redis-set 0 1000


## ZREVRANGE key start stop [WITHSCORE]
返回有序集合中指定区间内的成员，通过索引，分数从高到低
其中成员的位置按分数值递减来排列
具有相同分数值的成员按字典的逆序排列
除了成员按分数值递减的次排序之外，和ZRANGE命令一样


## ZREVRANGEBYSCORE key max min [WITHSCORES]
返回有序集合中指定分数区间内的成员，分数从高到低排序
逆序排列指定区间的有序集合
redis> ZADD redis-set 100 "zhangsan"
redis> ZADD redis-set 200 "lisi"
redis> ZADD redis-set 300 "wangwu"
redis> ZREVRANGEBYSCORE redis-set +inf -inf   // 逆序排列所有成员
1） "wangwu"
2） "lisi"
3） "zhangsan"


## ZREVRANK key member
返回有序集合中指定成员的排名，有序集合成员按分数值递减排序
redis> ZADD redis-set 100 "zhangsan"
redis> ZADD redis-set 200 "lisi"
redis> ZADD redis-set 300 "wangwu"
redis> ZREVRANK redis-set "lisi"
1

## ZSCORE key member
返回有序集合中成员的分数值
redis> ZSCORE redis-set "hello"
1

## ZUNIONSTORE destination numkeys key [...]
计算给定的一个或多个有序集合的并集，并存储在新的key中
重复的元素值会相加
redis> ZADD redis-set1 100 "hello" 200 "world"
redis> ZADD redis-set2 300 "foo" 400 "bar"
redis> ZUNIONSTORE redis-set 2 redis-set1 redis-set2
4

## ZSCAN key cursor [MATCH pattern] [COUNT count]
迭代有序集合中的元素
