Redis-list
****************************************************************

1. BLPOP key1 [key2] timeout
�Ƴ�����ȡ�б�ĵ�һ��Ԫ�أ�����б�û��Ԫ�ػ������б�ֱ���ȴ���ʱ���ֿɵ���Ԫ��Ϊֹ
����б�Ϊ�գ�����һ��nil
���򣬷���һ����������Ԫ�ص��б���һ��Ԫ���Ǳ�����Ԫ��������key���ڶ���Ԫ���Ǳ�������Ԫ�ص�ֵ



2. BRPOP key1 [key2] timeout
�Ƴ�����ȡ�б�����һ��Ԫ�أ�����б�û��Ԫ�ػ������б�ֱ���ȴ���ʱ���߷��ֿɵ���Ԫ��Ϊֹ
������ָ��ʱ����û���κ�Ԫ�ر��������򷵻�һ��nil�͵ȴ�ʱ��
��֮������һ����������Ԫ�ص��б���һ��Ԫ���Ǳ�����Ԫ��������key���ڶ���Ԫ���Ǳ�������Ԫ�ص�ֵ


3. BRPOPLPUSH source destination timeout
���б��е���һ��ֵ����������Ԫ�ز��뵽��һ���б��в���������
����б�û��Ԫ�ػ������б�ֱ���ȴ���ʱ���߷��ֿɵ���Ԫ��Ϊֹ
# �ǿ��б�
redis> BRPOPLPUSH msg reciver 500
"Hello World"
(3.38s)
redis> LLEN reciver
1
redis> LRANGE reciver 0 0
1) "Hello World"

# ���б�
redis> BRPOPLPUSH msg reciver 1
(nil)
(1.34s)



4. LINDEX key index
ͨ��������ȡ�б��е�Ԫ��
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
���б��Ԫ��ǰ���ߺ����Ԫ��
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
��ȡ�б���
redis> RPUSH redis-list "Hello"
1
redis> RPUSH redis-list "World"
2
redis> LLEN redis-list
2


7. LPOP key
�Ƴ�����ȡ�б�ĵ�һ��Ԫ��
redis> RPUSH redis-list "Hello"
1
redis> RPUSH redis-list "World"
2
redis> LPOP redis-list
"Hello"


8. LPUSH key value1 [value2]
��һ������ֵ���뵽�б�ͷ��
redis> LPUSH redis-list "Hello"
1
redis> LPUSH redis-list "World"
2
redis> LRANGE redis-list
1) "World"
2) "Hello"


9. LPUSHX key value
��һ������ֵ���뵽�Ѵ��ڵ��б�ͷ��
�б�����ʱ������Ч
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
��ȡ�б�ָ����Χ�ڵ�Ԫ��
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
�Ƴ��б�Ԫ��
COUNT��ֵ���������¼��֣�
	* count > 0: �ӱ�ͷ��ʼ���β�������Ƴ���VALUE��ȵ�Ԫ�أ�����ΪCOUNT
	* count < 0: �ӱ�β��ʼ���ͷ�������Ƴ���VALUE��ȵ�Ԫ�أ�����ΪCOUNT�ľ���ֵ
	* count = 0: �Ƴ�����������VALUE��ȵ�ֵ
����ֵ�����Ƴ�Ԫ�ص��������б�����ʱ�򷵻�0
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "world"
redis> RPUSH redis-list "hello"
redis> LREM redis-list -2 "hello"
2


12. LSET key index value
ͨ�����������б�Ԫ�ص�ֵ
����������������Χ�����һ���յ��б����LSETʱ������һ������
����ֵ��
	�����ɹ�������OK�����򷵻ش�����Ϣ
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
��һ���б�����޼�������˵�����б�ֻ����ָ�������ڵ�Ԫ�أ�����ָ������֮�ڵ�Ԫ�ض�����ɾ��
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
�Ƴ�����ȡ�б�����һ��Ԫ��
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
�Ƴ��б�����һ��Ԫ�أ�������Ԫ����ӵ���һ���б�����
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
���б������һ������ֵ
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
Ϊ�Ѵ��ڵ��б����ֵ���б��β��������б����ڣ�������Ч
redis> RPUSH redis-list "hello"
redis> RPUSH redis-list "world"
redis> RPUSHX redis-list "foo"
redis> RPUSHX redis-list "bar"


