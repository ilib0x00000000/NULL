#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
random模块：
	o random(): 产生1个[0,1)之间的浮点数
	o uniform(min, max): 生成一个指定区间内的数
	o seed(n):	设置随机数种子
	o randint(min, max):生成一个指定区间的整数
	o randrange(min, max, step):在指定的区段内产生一个随机数
	o choice(sequence):从给定的序列中随机返回一个对象
	o shuffle(sequence):把给定的序列重新排列
	o sample(sequence, count):从给定的序列中随机抽样
"""

import time
import random
import itertools

for i in xrange(3):
	print random.random(),
print 


for i in xrange(3):
	print random.uniform(10, 20),
print 

# 整数随机数生成
for i in xrange(3):
	print random.randint(1, 100),
print


# 段随机数生成
for i in xrange(3):
	print random.randrange(10, 50, 4),
print


# 选择随机元素
coins = {
	'heads':0,
	'tails':0
}
keys = coins.keys()

for i in xrange(1000):
	coins[random.choice(keys)] += 1
print coins
print


CHARS = ['J', 'Q', 'K', 'A']
SUITS = ['H', 'D', 'C', 'S']

pack = itertools.chain(xrange(2,11), CHARS)
packs = list(itertools.product(pack, SUITS))
print packs
# 洗牌
random.shuffle(packs)
print packs


# 随机抽样
swatch = ['s', 'e', 'c', 't', 'b', 'h', 'u', 'm']
print random.sample(swatch, 3)
print random.sample(swatch, 3)
print random.sample(swatch, 3)


"""
有些操作系统提供了一个随机数生成器
"""
# 1.创建一个随机数种子
# 2.创建一个系统随机数类
# 3.调用该类实例的API

seed = time.time()
sr = random.SystemRandom(seed)
print '\n系统随机数'
print sr.random()
print sr.random()
print sr.random()
