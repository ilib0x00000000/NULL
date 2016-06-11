#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-11 16:17:34 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
进程间的信号传递
"""

import time
import multiprocessing

def wait_for_event(e):
	print 'wait_for_event: starting'
	print 'wait_for_event: e.is_set()->', e.is_set()
	e.wait()
	print 'wait_for_event: e.is_set()->', e.is_set()

def wait_for_event_timeout(e, t):
	print 'wait_for_event_timeout: starting'
	print 'wait_for_event_timeout: e.is_set()->', e.is_set()
	e.wait(t)
	print 'wait_for_event_timeout: e.is_set()->', e.is_set()


if __name__ == '__main__':
	e = multiprocessing.Event()

	p1 = multiprocessing.Process(target=wait_for_event, name='block', args=(e,))
	p2 = multiprocessing.Process(target=wait_for_event_timeout, name='nonblock', args=(e,2))

	p1.start()
	p2.start()

	print 'main: waiting before calling Event.set()'

	time.sleep(3)
	e.set()

	print 'main: event is set'
