#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-25 21:24:40 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

import logging
import threading

logging.basicConfig(level=logging.DEBUG, format='(%(threadName)-10s) %(message)s')

def worker_with(lock):
	with lock:
		logging.debug('lock acquire via with')

def worker_no_with(lock):
	lock.acquire()

	try:
		logging.debug('lock acquire directly')
	finally:
		lock.release()

lock = threading.Lock()

w = threading.Thread(target=worker_with, args=(lock,))
nw = threading.Thread(target=worker_no_with, args=(lock,))

w.start()
nw.start()
