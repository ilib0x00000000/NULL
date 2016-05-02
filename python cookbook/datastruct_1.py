#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
collections库：
	Counter：作为一个容器，可以跟踪相同的值增加了多少次
		Counter.update():可以更新容器的元素及其值
		Counter.elements():返回Counter容器中的所有元素（迭代器）
		Counter.most_common():生成一个序列，其中包含N个最常遇到的输入值及其相应计数
		Counter还支持算数运算，包括 + , - , & , |


	defaultdict:创建一个字典，获得字典中没有的元素时，则返回指定的值


	deque:双端队列，支持从任意一端增加和删除元素(线程安全)
		deque.extend():在后面增加，将参数中的序列，一个一个元素的添加到队列中
		deque.append():在后面增加，将参数中的序列作为一个整体添加到队列中
		deque.extendleft():在队列的前面增加，将参数中的序列反向添加到队首
		deque.appendleft():在队列的前面增加，将参数中的序列作为一个整体添加到队首
		deque.pop():删除队尾的元素
		deque.popleft():删除队首的元素
		deque.rotate():参数正值，则将后面的元素切到队首，参数负值，则将前面的元素切到队尾


	namedtuple:命名元组,参数就是新类名和一个包含元素名的字符串
		命名元组实际是创建一个类,类的常用参数有3个
		1. 新类名
		2. 包含各元素名的字符串(出现重复、关键字会报异常)
		3. 当事先不知道要创建的namedtuple的各元素时，可以使用关键字对元素名重命名



	OrderedDict:带顺序的字典
		字典的子类，同时会记住各元素在字典中的顺序
"""

import time
import threading
import collections


d1 = {}
d1['A'] = 1
d1['B'] = 2
d1['C'] = 3

d2 = {}
d2['C'] = 3
d2['A'] = 1
d2['B'] = 2


print d1 == d2


d3 = collections.OrderedDict()
d3['A'] = 1
d3['B'] = 2
d3['C'] = 3

d4 = collections.OrderedDict()
d4['C'] = 3
d4['A'] = 1
d4['B'] = 2

print d3 == d4

print d3
print d4

#****************************************************************************************************************
Person = collections.namedtuple('Humer', 'name sex age')


print 'Type of namedtuple:', type(Person)

bob = Person(name='bob', sex=True, age=12)
mary = Person(name='mary', sex=False, age=21)

print bob
print mary

print bob.name, bob.sex, bob.age
print mary.name, mary.sex, mary.age


for item in bob:
	print item

#****************************************************************************************************************

d = collections.deque(xrange(10))
print d

d.rotate(2)
print d

d.rotate(-5)
print d


candle = collections.deque(xrange(5))

def burn(direction, nextSource):
	while True:
		try:
			nexts = nextSource()
		except IndexError:
			break
		else:
			print '%s : %s' % (direction, nexts)
			time.sleep(0.1)
	print '%s done' % direction

	return


left = threading.Thread(target=burn, args=('Left', candle.popleft))
right = threading.Thread(target=burn, args=('Right', candle.pop))


left.start()
right.start()

left.join()
right.join()


d = collections.deque('abcde')

print d
print len(d)
print d[0]
print d[-1]


d.extend('xxxxx')
print d

d.append('hhhhh')
print d

d.extendleft('xyz')
print d

d.appendleft('hhhhhhhhhh')
print d


d.pop()
print d

d.popleft()
print d

#****************************************************************************************************************

def ret_value():
	return -1

d = collections.defaultdict(ret_value, {'a':'test', 'foo':'bar'})

print d
print d['a']
print d['foo']
print d['test']


print collections.Counter(['a', 'b', 'a', 'c', 'a', 'b'])
print collections.Counter({'a':3, 'b':1, 'c':2})
print collections.Counter(a=2, b=1, c=3)

c = collections.Counter()

c.update('lkhkljhkj')
print c

c.update({'a':12, 'j':1, 'h':8})
print c


for item in c.elements():
	print item,
print 

d = collections.Counter()

with open('/usr/share/dict/words', 'rb') as f:
	for line in f:
		d.update(line.strip().lower())


print 'Most Common: '
print d.most_common(10)
