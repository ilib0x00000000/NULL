#!/usr/bin/env python3

"""Python抽象类

Python抽象类是通过abc模块中的元类和装饰器定义的
定义一个抽象基类的时候有三个步骤：
	1. 该类的元类设置成 metaclass=abc.ABCMeta
	2. 定义抽象方法： @abc.abstractmethod
	3. 抽象基类中实现类方法： __subclasshook__(cls, subclass)

ABCMeta类保证抽象基类不会被实例化，但是，一个提供了所有必须实现的方法的子类可以被实例化
这个元类型会在执行__new__()的时候调用抽象基类中的__subclasshook__()特殊方法，如果这个方法返回NotImplemented，就会抛出一个异常，指出当前类没有实现所有必须的方法

内置容器的完整图谱都是用抽象基类来表示的
底层的特性包括Container、Iterable和Sized，而它们同时也是高级构造过程的一部分。
它们需要一些特殊方法，分别是__contains__()、__iter__()和__len__()。

* Sequence是list的抽象基类
* MutableSequence是tuple的抽象基类
* MutableMapping是dict的抽象基类，它扩展了Mapping类，但是没有内置具体的实现
* Set是frozenset的抽象基类
* MutableSet是set的抽象基类
"""


from abc import ABCMeta, abstractmethod

class AbstractSetting(metaclass=ABCMeta):
	"""定义一个抽象基类
	"""
	__slot__ = ()

	@abstractmethod
	def bet(self, hand):
		return 1


	@abstractmethod
	def recond_win(self, hand):
		pass


	@abstractmethod
	def recond_loss(self, hand):
		pass


	@classmethod
	def __subclasshook__(cls, subclass):
		"""由于抽象基类中定义了__slots__属性，所以通过子类的__mro__向上查找父类的__dict__时，
		是不会找到抽象基类中的方法名的
		"""
		if cls is Hand:
			if (
					any("bet" in B.__dict__ for B in subclass.__mro__) and
					any("recond_win" in B.__dict__ for B in subclass.__mro__) and
					any("recond_loss" in B.__dict__ for B in subclass.__mro__)
				):
				return True

		return NotImplemented




if __name__ == '__main__':
	try:
		class SimpleBroken(AbstractSetting):
			def bet(self, hand):
				return 1

		s = SimpleBroken()

	except TypeError as err:
		print(err)
		class SimpleBroken(AbstractSetting):
			def bet(self, hand):
				return 1

			def recond_win(self, hand):
				pass

			def recond_loss(self, hand):
				pass

		s = SimpleBroken()