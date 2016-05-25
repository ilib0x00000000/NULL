#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-25 20:50:20 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

import time
import logging
import threading

logging.basicConfig(level=logging.DEBUG, format='(%(threadName)-10s) %(message)s')

def lock_holder(lock):
	logging.debug('Starting')
	while True:
		lock.acquire()
		try:
			logging.debug('Holding')
			time.sleep(0.5)
		finally:
			logging.debug('Not Holding')
			lock.release()
		time.sleep(0.5)
	return

def worker(lock):
	logging.debug('Starting')

	num_tries = 0
	num_acquires = 0

	while num_acquires<3:
		time.sleep(0.5)
		logging.debug('Trying to acquire')
		have_it = lock.acquire(0)

		try:
			num_tries += 1
			if have_it:
				logging.debug('iteration %d: acquire', num_tries)
				num_acquires += 1
			else:
				logging.debug('iteration %d: not acquire', num_tries)
		finally:
			if have_it:
				lock.release()
				logging.debug('done after %d iteration', num_tries)

lock = threading.Lock()

holder = threading.Thread(target=lock_holder, args=(lock,), name='LockHolder')
holder.setDaemon(True)
holder.start()

worker = threading.Thread(target=worker, args=(lock,), name='Worker')
worker.start()
