#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-05-17 15:51:21 
# @Author  : ilib0x00000000
# @email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

try:
	from xml.etree import cElementTree as ElementTree
except:
	from xml.etree import ElementTree

"""
解析XML有两种方式：
	1. 基于文档（当文档过大时，占用内存多）
	2. 基于事件

解析XML时主要的两个对象：
	1. ElementTree对象(树)，解析xml文件得到
		iter([nodename]):查看所有的节点或者指定的节点
		find(XPath):以某种方式查找节点
		findall(XPath):以某种方式查找所有节点

	2. Element对象(节点)，由ElementTree对象方法得到
		tag:节点的名称
		text:节点的内容
		tail:该节点结束标签之后，下一节点标签开始之前的内容
		attrib:节点中的属性与值的集合，类似字典，通过get取出指定元素
"""

xml_filename = ''					# 待填充


def print_node_attr(node):
	print node.tag,					# 得到节点的tag属性
	print node.attrib,				# 得到节点的attrib属性，类似字典
	print node.text,				# 得到节点的text属性
	print node.tail,				# 得到节点的tail属性	


with open(xml_filename, 'rb') as f:
	tree = ElementTree.parse(f)			# 得到ElementTree对象

	nodes = tree.iter()					# 得到所有节点对象(序列)
	for node in nodes:
		print_node_attr(node)

	tag_name = ''						# 待填充
	nodes = tree.iter(tag_name)			# 得到指定节点对象
	for node in nodes:
		print_node_attr(node)

	find_nodes_name = ''						# 待填充
	find_nodes = tree.find(find_nodes_name)		# 查找文档节点

	for node in find_nodes:
		print_node_attr(node)