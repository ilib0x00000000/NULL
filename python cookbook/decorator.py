#!/usr/bin/env python3


"""编写装饰器
装饰器分为两种：
	* 无参装饰器
	* 带参装饰器
"""

import functools


# 无参装饰器
def decorator_without_arg(function):
	@functools.wraps(function)   # 确保原始函数的函数名和docstring在新生成的函数中都会被保留
	def wrapped(*args, **kwargs):   # 这里的参数是原始函数接受的参数
		# TODO
		result = function(*args, **kwargs)
		# TODO
		return result   # 如果被修饰的函数有返回值

	return wrapped



# 带参装饰器
def decorator_with_arg(arg0, arg1):
	"""arg0,arg1是装饰器接受的参数
	"""
	def concrete_decorator(function):
		@function.wraps(function)  # 确保原始函数的函数名和docstring在新生成的函数中都会被保留
		def wrapped(*args, **kwargs):
			"""args,kwargs是原始函数接受的函数
			"""
			# TODO
			result = function(*args, **kwargs)
			# TODO
			return result

		return wrapped
	return concrete_decorator


# 定义无参装饰器函数
def decorator_without_arg_demo(function):
	@functools.wraps(function)
	def wrapped(*args, **kwargs):
		print('在运行被修饰的函数之前')
		result = function(*args, **kwargs)
		print('在运行被修饰的函数之后')
		return result
	return wrapped


# 定义带参装饰器函数
def decorator_with_arg_demo(arg0, arg1):
	def concrete_decorator(function):
		@functools.wraps(function)
		def wrapped(*args, **kwargs):
			print('在运行被修饰的函数之前')
			print('装饰器接受的第一个参数: %s' % arg0)
			print('装饰器接受的第二个参数: %s' % arg1)
			result = function(*args, **kwargs)
			print('在运行被修饰的函数之后')
			return result

		return wrapped
	return concrete_decorator



@decorator_with_arg_demo('aaaaaa', 'bbbbbbb')
def demo(name, value):
	print('函数%s接受了参数%s' % (__name__, name))
	print('函数%s接受了参数%s' % (__name__, value))



@decorator_without_arg_demo
def test(name, value):
	print('函数%s接受了参数%s' % (__name__, name))
	print('函数%s接受了参数%s' % (__name__, value))



if __name__ == '__main__':
	demo('0', '1')
	test('+', '-')