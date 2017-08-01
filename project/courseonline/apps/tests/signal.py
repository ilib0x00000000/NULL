# -*- coding:utf-8 -*-

"""
__author__ : ilib0x00000000
__datetime__ : 2017/7/28 7:33

信号：
Model signals
    pre_init                    # django的modal执行其构造方法前，自动触发
    post_init                   # django的modal执行其构造方法后，自动触发
    pre_save                    # django的modal对象保存前，自动触发
    post_save                   # django的modal对象保存后，自动触发
    pre_delete                  # django的modal对象删除前，自动触发
    post_delete                 # django的modal对象删除后，自动触发
    m2m_changed                 # django的modal中使用m2m字段操作第三张表（add,remove,clear）前后，自动触发
    class_prepared              # 程序启动时，检测已注册的app中modal类，对于每一个类，自动触发
Management signals
    pre_migrate                 # 执行migrate命令前，自动触发
    post_migrate                # 执行migrate命令后，自动触发
Request/response signals
    request_started             # 请求到来前，自动触发
    request_finished            # 请求结束后，自动触发
    got_request_exception       # 请求异常后，自动触发
Test signals
    setting_changed             # 使用test测试修改配置文件时，自动触发
    template_rendered           # 使用test测试渲染模板时，自动触发
Database Wrappers
    connection_created          # 创建数据库连接时，自动触发
"""

from django.db.models.signals import pre_init, post_init
from django.db.models.signals import pre_save, post_save
from django.db.models.signals import pre_delete, post_delete


def storage_pre(sender, **kwargs):
    print '即将存储一条数据'


def storage_over(sender, **kwargs):
    print '数据已经存储结束'


pre_save.connect(storage_pre)
post_save.connect(storage_over)

# 这里注册的函数，不管哪个模型的对象存储时，都会触发信号，然后回调该函数


def delete_pre(sender, **kwargs):
    print '即将删除一条数据'


def delete_over(sender, **kwargs):
    print '数据已经删除完毕'


pre_delete.connect(delete_pre)
post_delete.connect(delete_over)
