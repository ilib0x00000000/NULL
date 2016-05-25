#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-25 18:56:51 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************


import logging
import threading

logging.basicConfig(level=logging.DEBUG, format='(%(threadName)-10s) %(message)s')

class MyThreadWithArgs(threading.Thread):
	def __init__(self, group=None, name=None, target=None, args=(), kwargs=None, verbose=None):
		super(self.__class__, self).__init__(group=group, name=name, target=target, verbose=verbose)
		self.args = args
		self.kwargs = kwargs
		return

	def run(self):
		logging.debug('run with %s and %s', self.args, self.kwargs)
		return

for i in range(5):
	t = MyThreadWithArgs(args=(i,), kwargs={'a':'A', 'b':'B'})
	t.start()
