#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
functools模块：
	partial: 偏函数，将一个函数转换成另一个新的函数，但是函数的参数可能依据需要发生变化
	update_wrapper：创建偏函数时，将原函数的属性传递给新函数
	@wraps：在修饰器中使用该修饰符，就是对修饰器返回的函数应用update_wrapper函数
"""


from functools import partial, update_wrapper, wraps



def test_partial(numstr):
	"""在将整数字符串转换成数字时，默认的是把字符串内容当做十进制数字，现在数字全部是十六进制的
	"""
	print '16进制数: ', int(numstr)
	int16 = partial(int, base=16)

	num = int16(numstr)
	print '10进制数: ', num


def origin_func(a, b=2):
	"""Docstrings for origin_func().
	"""
	print 'called origin_func with:', (a,b)


def show_details(f):
	"""Show details of a callable object
	"""
	print '__name__:',
	try:
		print f.__name__
	except AttributeError:
		print 'no __name__'

	print '__doc__:', repr(f.__doc__)
	return 


def test_updatewrapper():
	"""在创建偏函数时，新的函数不会包含原函数的全部属性，需要通过update_wrapper函数传递
	"""
	p_func = partial(origin_func, b=999)
	p_func('这是偏函数调用'.decode('utf-8'))
	show_details(p_func)

	print 'update_wrapper: '
	update_wrapper(p_func, origin_func)
	show_details(p_func)


def simple_decorator(f):		# f是被修饰函数
	@wraps(f)
	def decorated(a='decorated defaults', b=1):
		print 'decorated:', (a,b)
		f(a,b=b)
		return
	return decorated


def myfunc(a,b=2):
	"""Docstring for myfunc
	"""
	print 'myfunc:', (a,b)
	return


@simple_decorator
def decorated_myfunc(a,b):
	"""被修饰函数
	"""
	myfunc(a,b)
	return


def test_wraps():
	"""装饰器：接受函数作为参数，返回函数的函数
	在装饰器中调用wraps函数，就是将参数中的函数的属性传递给返回的函数
	"""
	show_details(myfunc)
	print '\n\n'

	wrapped_func = simple_decorator(myfunc)
	show_details(wrapped_func)
	print '\n\n'

	show_details(decorated_myfunc)



if __name__ == '__main__':
	test_partial('15353')
	test_updatewrapper()
	test_wraps()