#!/usr/bin/env  python
# -*- coding:utf-8 -*-

import time
import threading


def worker():
	print threading.currentThread().getName(), 'Starting'
	time.sleep(4)
	print threading.currentThread().getName(), 'Exiting'

def my_service():
	print threading.currentThread().getName(), 'Starting'
	time.sleep(2)
	print threading.currentThread().getName(), 'Exiting'

t = threading.Thread(name = 'my_service', target = my_service)
w = threading.Thread(name = 'worker', target = worker)
s1 = threading.Thread(target = worker)	
s2 = threading.Thread(target = my_service)	

t.start()
w.start()
s1.start()
s2.start()

# output
# my_service Starting
# worker Starting
# Thread-1 Starting
# Thread-2 Starting
# my_service Exiting
# worker Exiting
# Thread-1 Exiting
# Thread-2 Exiting