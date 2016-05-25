#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-25 18:44:03 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
创建线程的方式：
	继承Thread类，覆盖run方法
"""


import logging
import threading

logging.basicConfig(level=logging.DEBUG, format='(%(threadName)-10s) %(message)s')

class MyThread(threading.Thread):
	def run(self):
		logging.debug('running')
		return

for i in range(5):
	t = MyThread()
	t.start()