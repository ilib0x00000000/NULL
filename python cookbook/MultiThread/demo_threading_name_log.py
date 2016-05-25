#!/usr/bin/env  python
# -*- coding:utf-8 -*-

import time
import logging
import threading

# 配置日志
logging.basicConfig(level=logging.DEBUG, format='[%(levelname)s] (%(threadName)-10s) %(message)s')


def worker():
	logging.debug('Starting')
	time.sleep(2)
	logging.debug('Exiting')

def my_service():
	logging.debug('Starting')
	time.sleep(3)
	logging.debug('Exiting')

t = threading.Thread(name = 'my_service', target = my_service)
w = threading.Thread(name = 'worker', target = worker)
s1 = threading.Thread(target = worker)	
s2 = threading.Thread(target = my_service)	

t.start()
w.start()
s1.start()
s2.start()