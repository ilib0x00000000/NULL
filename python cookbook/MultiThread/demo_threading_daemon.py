#!/usr/bin/env  python
# -*- coding:utf-8 -*-

import time
import logging
import threading

# 配置日志
logging.basicConfig(level=logging.DEBUG, format='(%(threadName)s) %(message)s')


def daemon():
	logging.debug('Starting')
	time.sleep(2)
	logging.debug('Exiting')

def non_daemon():
	logging.debug('Starting')
	logging.debug('Exiting')

d = threading.Thread(name='daemon', target=daemon)
d.setDaemon(True)

t = threading.Thread(name='non_daemon', target=non_daemon)

d.start()
t.start()

# output
# (daemon) Starting
# (non_daemon) Starting
# (non_daemon) Exiting