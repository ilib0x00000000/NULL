#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-25 19:20:37 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

import time
import logging
import threading

logging.basicConfig(level=logging.DEBUG, format='(%(threadName)-10s) %(message)s')

def wait_for_event(e):
	logging.debug('wait_for_event starting')
	event_is_set = e.wait()
	logging.debug('event set:%s', event_is_set)


def wait_for_enevt_timeout(e, t):
	while not e.isSet():
		logging.debug('wait_for_enevt_timeout starting')
		event_is_set = e.wait(t)
		logging.debug('event set:%s', event_is_set)

		if event_is_set:
			logging.debug('processing event')
		else:
			logging.debug('doing other work')

e = threading.Event()

t1 = threading.Thread(name='block', target=wait_for_event, args=(e,))
t2 = threading.Thread(name='nonblock', target=wait_for_enevt_timeout, args=(e,2))

t1.start()
t2.start()

logging.debug('waiting before calling Event.set()')
time.sleep(3)
e.set()
logging.debug('Event is set')