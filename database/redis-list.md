Redis-list
****************************************************************

1. BLPOP key1 [key2] timeout
移除并获取列表的第一个元素，如果列表没有元素会阻塞列表直到等待超时或发现可弹出元素为止
如果列表为空，返回一个nil
否则，返回一个含有两个元素的列表，第一个元素是被弹出元素所属的key，第二个元素是被弹出的元素的值



2. BRPOP key1 [key2] timeout
移出并获取列表的最后一个元素，如果列表没有元素会阻塞列表直到等待超时或者发现可弹出元素为止
假如在指定时间内没有任何元素被弹出，则返回一个nil和等待时长
反之，返回一个含有两个元素的列表，第一个元素是被弹出元素所属的key，第二个元素是被弹出的元素的值


3. BRPOPLPUSH source destination timeout
从列表中弹出一个值，将弹出的元素插入到另一个列表中并返回它，
如果列表没有元素会阻塞列表直到等待超时或者发现可弹出元素为止
# 非空列表
redis> BRPOPLPUSH msg reciver 500
"Hello World"
(3.38s)
redis> LLEN reciver
1
redis> LRANGE reciver 0 0
1) "Hello World"

# 空列表
redis> BRPOPLPUSH msg reciver 1
(nil)
(1.34s)



4. LINDEX key index
通过索引获取列表中的元素
redis> LPUSH redis-list "World"
1
redis> LPUSH redis-list "Hello"
2
redis> LINDEX redis-list 0
"Hello"
redis> LINDEX redis-list -1
"World"
redis> LINDEX redis-list 3
(nil)

5. LINSERT key BEFOREE|AFTER pivotvalue
在列表的元素前或者后插入元素
redis> RPUSH redis-list "foo"
1
redis> RPUSH redis-list "bar"
2
redis> LINSERT redis-list BEFORE "bar" "yes"
3
redis> LRANGE redis-list 0 -1
1) "foo"
2) "yes"
3) "bar"

6. LLEN key
获取列表长度
redis> RPUSH redis-list "Hello"
1
redis> RPUSH redis-list "World"
2
redis> LLEN redis-list
2


7. LPOP key
移出并获取列表的第一个元素
redis> RPUSH redis-list "Hello"
1
redis> RPUSH redis-list "World"
2
redis> LPOP redis-list
"Hello"


8. LPUSH key value1 [value2]
将一个或多个值插入到列表头部
redis> LPUSH redis-list "Hello"
1
redis> LPUSH redis-list "World"
2
redis> LRANGE redis-list
1) "World"
2) "Hello"


9. LPUSHX key value
将一个或多个值插入到已存在的列表头部
列表不存在时操作无效
redis> LPUSH redis-list "Hello"
1
redis> LPUSHX redis-list "World"
2
redis> LPUSHX new-list "Demo"
0
redis> LRANGE redis-list 0 -1
1) "World"
2) "Hello"


10. LRANGE key start stop
获取列表指定范围内的元素
redis> LPUSH redis-list "World"
1
redis> LPUSH redis-list "Hello"
2
redis> LPUSHX redis-list "....."
3
redis> LRANGE redis-list 0 -1
1) "...."
2) "Hello"
3) "World"


11. LREM key count value
移除列表元素
COUNT的值可以是以下几种：
	* count > 0: 从表头开始向表尾搜索，移除与VALUE相等的元素，数量为COUNT
	* count < 0: 从表尾开始向表头搜索，移除与VALUE相等的元素，数量为COUNT的绝对值
	* count = 0: 移除表中所有与VALUE相等的值
返回值：被移除元素的数量。列表不存在时候返回0
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "world"
redis> RPUSH redis-list "hello"
redis> LREM redis-list -2 "hello"
2


12. LSET key index value
通过索引设置列表元素的值
当索引参数超过范围，或对一个空的列表进行LSET时，返回一个错误
返回值：
	操作成功，返回OK，否则返回错误信息
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "foo"
redis> RPUSH redis-list "hello"
redis> LSET redis-list 0 "bar"
redis> LRANGE redis-list 0 -1
1) "bar"
2) "hello"
3) "foo"
4) "hello"


13. LTRIM key start stop
对一个列表进行修剪，就是说，让列表只保存指定区间内的元素，不在指定区间之内的元素都将被删除
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "world"
redis> RPUSH redis-list "foo"
redis> RPUSH redis-list "bar"
redis> LTRIM redis-list 1 -1
OK
redis> LRANGE redis-list 0 -1
1) "world"
2) "foo"
3) "bar"


14. RPOP key
移除并获取列表的最后一个元素
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "world"
redis> RPUSH redis-list "foo"
redis> RPUSH redis-list "bar"
redis> RPOP redis-list
redis> LRANGE redis-list 0 -1
1) "hello"
2) "world"
3) "foo"


15. RPOPLPUSH source destination
移除列表的最后一个元素，并将该元素添加到另一个列表并返回
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "world"
redis> RPUSH redis-list "foo"
redis> RPUSH redis-list "bar"
redis> RPOPLPUSH redis-list new-list
"bar"
redis> LRANGE redis-list 0 -1
1) "hello"
2) "world"
3) "foo"


16. RPUSH key value1 [value2]
在列表中添加一个或多个值
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "world"
redis> RPUSH redis-list "foo"
redis> RPUSH redis-list "bar"
redis> LRANGE redis-list 0 -1
1) "hello"
2) "world"
3) "foo"
4) "bar"


17. RPUSHX key value
为已存在的列表添加值到列表的尾部，如果列表不存在，操作无效
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "world"
redis> RPUSHX redis-list "foo"
redis> RPUSHX redis-list "bar"


