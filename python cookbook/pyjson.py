#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""使用json

参考：[http://blog.csdn.net/woods2001/article/details/7864929]

当python Dict中带有自定义的对象要转成json对象时，有两种处理方法：
1. json.dump()和json.load()都有指定的回调函数参数，可以通过指定回调函数来解决自定义对象转换
2. 继承json.JSONDecoder和json.JSONEncoder类，覆盖掉原始的转换方法，重新定义编码、解码方式


Basic Usage:
json.dump(obj, fp, skipkeys=False, ensure_ascii=True, check_circular=True, allow_nan=True,
		cls=None, indent=None, separators=None, encoding='utf-8', default=None, sort_keys=False, **kwargs)
参数：
	obj: 
	fp:
	skipkeys=False: 如果选项为True，则字典的键不是基本类型就会跳过，而不是抛出异常
	ensure_ascii=True: 非ASCII码会以\uXXXX序列的形式输出，输出的字符串只会由ASCII码字符组成。如果此选项为False，则输出的字符串可能包含Unicode字符
	check_circular=True: 如果这个选项设置为False，则容器类型的循环引用检测会被跳过，可能导致栈溢出，或者更严重的情况
	allow_nan=True: 如果这个选项被设置为False，则当数值超出范围时会引发ValueError
	cls=None:
	indent=None: 缩进，如果这个参数被设置成非负正数，JSON数组元素和对象之间在输出时，会间隔指定的个数个空格
	separators=None: 分隔符，在网络上传输字节时，字节的大小很关键，可以通过separators来压缩字节的大小
	encoding='utf-8':
	default=None: default(obj)是一个函数，返回关于obj序列化的版本或者抛出一个异常。默认是简单的抛出一个ValueError，当要装换的Dict中有自定义的对象时，可以
	         通过default指定的函数，将该对象转换成json对象
	sort_keys=False: 输出时json对象会按照键排序
	**kwargs:


json.dumps(obj, skipkeys=False, ensure_ascii=True, check_circular=True, allow_nan=True, cls=None, 
		indent=None, separators=None, encoding='utf-8', default=None, sort_keys=False, **kwargs)
	类似dump()函数，只是序列化之后的结果以字符串的形式返回



json.load(fp [, encoding [, cls[, object_hook[, parse_float [, parse_int[, parse_constant[, object_pairs_hook[, **kwargs]]]]]]]])
参数：
	fp: 从指定的文件描述符中读取数据反序列化
	encoding: 编码
	cls: 
	object_hook: 回调函数，将Dict中的对象还原成原来的对象的函数
	parse_float: 
	parse_int:
	parse_constant: 如果给出了这个参数的实现，当json对象中出现'-Infinity', 'Infinity', 'NaN'中的任意一个，就会回调该函数
	object_pairs_hook:
	**kwargs:


json.loads(S[, encoding[, cls[, object_hook[, parse_float[, parse_int[, parse_constant[, object_pairs_hook[, **kwargs]]]]]]]])
参考json.load()方法


json.JSONEncoder
json.JSONDecoder
"""


import json
from StringIO import StringIO


def obj2dict(obj):
	"""将自定义的对象转换成Dict
	"""
	d = {}
	d['__class__'] = obj.__class__.__name__
	d['__module__'] = obj.__module__
	d.update(obj.__dict__)
	return d



def dict2obj(dict_):
	"""将Dict中的对象还原成原来的对象
	"""
	if '__class__' in dict_:
		class_name  = dict_.pop('__class__')
		module_name = dict_.pop('__module__')
		module = __import__(module_name)
		class_ = getattr(module, class_name)

		kwargs = dict((key.encode('ascii'), value) for key,value in dict_.items())
		inst = class_(**kwargs)
	else:
		inst = dict_
	return inst



# 常规使用
io = StringIO()
json.dump({'a':[1, 2, 3], 'b':'string', 'c':None, 'd':1.0, 'e':5, 'f':'这是一个字符串'}, io, ensure_ascii=False, indent=4)
print io.getvalue()





class Test():
	def __hash__(self):
		return hash(id(self))

t = Test()

# 带自定义对象的python Dict
io = StringIO()
json.dump({'a':t, 'c':'obj'}, io, default=obj2dict, indent=4)
print io.getvalue()



# 加载带特殊对象的json数据
load = json.load(io.getvalue(), object_hook=dict2obj)
print load

