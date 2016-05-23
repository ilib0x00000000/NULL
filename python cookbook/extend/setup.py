#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-23 21:56:17 
# @Author  : ilib0x00000000
# @email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

from distutils.core import setup,Extension

MOD = 'Cextends'

setup(name=MOD, ext_modules = [Extension(MOD, sources=['Pywrappers.c'])])


"""
编译方式：python setup.py build

测试：编译成功后，在编译的目录下会产生build目录，到该目录下启动Python解释器导入该模块即可测试
"""
