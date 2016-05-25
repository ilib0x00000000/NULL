#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-25 19:50:26 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

import time
import random
import logging
import threading

logging.basicConfig(level=logging.DEBUG, format='(%(threadName)-10s) %(message)s')


class Counter(object):
	def __init__(self, start=0):
		self.lock = threading.Lock()
		self.value = start

	def increment(self):
		logging.debug('wait for lock')
		self.lock.acquire()

		try:
			logging.debug('....Acquired lock....')
			self.value = self.value+1
			logging.debug('....add 1 over...')
		finally:
			self.lock.release()

def worker(c):
	for i in range(2):
		pause = random.random()
		logging.debug('sleeping %0.02f', pause)
		time.sleep(pause)
		c.increment()
	logging.debug('done')

counter = Counter()

for x in xrange(2):
	t = threading.Thread(target=worker, args=(counter,))
	t.start()

logging.debug('waiting for worker threads')

main_thread = threading.currentThread()

for i in threading.enumerate():
	if i is not main_thread:
		i.join()

logging.debug('Counter: %d', counter.value)
