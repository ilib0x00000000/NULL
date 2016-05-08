#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
上下文管理器：
	简单的理解就是with代码块中的语句


上下文协议实现了两个方法：
	__enter__:返回一个对象
	__exit__: 清理使用的资源
"""

import contextlib


class ContextManagerOpen(object):
	"""模仿open函数创建一个上下文管理器
	"""
	def __init__(self, file_name, oper_mode='rb'):
		self.file_name = file_name
		self.oper_mode = oper_mode


	def __enter__(self):
		"""如果with语句中有as语句，则此函数应该返回一个对象
		"""
		self.obj = open(self.file_name, self.oper_mode)
		return self.obj


	def __exit__(self, exc_type, exc_value=None, exc_traceback=None):
		"""若此函数返回True，则不对异常处理
		若此函数返回False，则异常抛给with之外的语句处理
		"""
		self.obj.close()
		if exc_value:
			print 'error.....'
			return False
		return True
		
try:
	with ContextManagerOpen('a.txt', 'rb') as f:
		f.write('xyz')
except IOError:
	print 'can\'t open file'
print 


@contextlib.contextmanager
def make_context():
	"""将一个生成器转换成上下文管理器，生成器只应该返回一个对象
	"""
	print 'enter...'
	try:
		yield 'one'
	except RuntimeError:
		print 'error...'
	finally:
		print 'exit...'


print 'Normal:'
with make_context() as s:
	print s
print


# 如果上下文环境中出现异常，则异常会抛给生成器函数处理，若生成器能处理该异常则由生成器处理，
# 否则由上下文代码块之外的语句处理
print 'Handle exception'
with make_context() as s:
	raise RuntimeError('Show example of handling an error')
print 


print 'Unhandle exception'
try:
	with make_context() as s:
		raise ValueError('Show example of unhandling an error')
except Exception:
	print '.............'
