#!/usr/bin/env  python
# -*- coding:utf-8 -*-

'''
Python使用Memcached:
[参考](http://www.cnblogs.com/lintong/p/4383212.html)
[Memcached使用教程](http://blog.csdn.net/hexiaodouaipiqiu/article/details/53002473)

安装Memcached
$ sudo apt-get install memcached

启动Memcached
$ memcached -d -m 128 -p 22222 -u root -c 1024 -l 127.0.0.1 -P /tmp/memcached.pid -s /tmp/memcached.sock
或 $ /etc/init.d/memcached start

[下载Memcached-Python插件](https://www.tummy.com/software/python-memcached/)
安装Memcached-Python插件:
tar -zxvf python-memcached-latest.tar.gz
sudo python setup.py install


memcached命令格式:<command name> <key> <flags> <exptime> <bytes>\r\n
<command name>
    * set:
    * add: 指明服务器没有该键时写入内存
    * replace: 只在服务器有该键时写入内存

<key>
客户端指定的键

<flags>
是客户端用来存储自定义信息的字段

<exptime>
是设置的有效期,如果设为0,则永不过期

<bytes>
是数据块

取回命令: get <key>* \r\n
<key>*表示一个或多个键值

删除命令: delete <key> <time>\r\n
<time>表示在该段时间内,数据被放入delete队列,无法通过get获得,也无法通过add,replace设置
'''

import memcache

class MemcachedClient():
    '''Python memcached客户端操作
    '''
    def __init__(self, host_list):
        self.__mc = memcache.Client(host_list)    # 创建一个memcache对象

    def set(self, key, value):
        result = self.__mc.set('name', 'John')
        return result

    def get(self, key):
        value = self.__mc.get(key)
        return value

    def delete(self, key):
        result = self.__mc.delete(key)
        return result

if __name__ == '__main__':
    mc = memcache.Client(['127.0.0.1:11211'], debug=0)

    # 设置键值对
    mc.set('foo', 'bar')

    # 返回指定的键,若memcache中存在该键对应的值,则返回该值,否则返回None
    value = mc.get('foo')
    print value

    # 删除键值对
    result = mc.delete('foo')

    value = mc.get('foo')
    if value:
        print 'value: %s' % value
    else:
        print 'no value of key<foo>'

'''
python-memcached API:
1. @set(key, value, time=0, min_compress_len=0)
设置键值对:time用于设置超时,min_compress_len表示是否设置zlib压缩

2. @set_multi(mapping, time=0, key_prefix='', min_compress_len=0)
设置多组键值,key_prefix是key的前缀

3. @add(key, value, time=0, min_compress_len=0)
添加一个键值对

4. @replace(key, value, time=0, min_compress_len=0)
替换value

5. @get(key)
根据key去获取value,出错返回None

6. @get_multi(keys, key_prefix='')
获取多组键值对,返回是一个字典

7. @delete(key, time=0)
删除指定的key

8. @incr(key, delta=1)
自增变量加上delta,默认加1
'''
