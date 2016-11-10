#!/usr/bin/env  python
# -*- coding:utf-8 -*-

# 数据库配置
import os

'''
数据库的配置主要字段:
    ENGINE
    NAME
    USER
    PASSWORD
    HOST
    PORT
'''

NAME = os.getenv('DATABASE_NAME')
USER = os.getenv('DATABASE_USER')
PASSWORD = os.getenv('DATABASE_PASSWORD')
HOST = os.getenv('DATABASE_HOST')
PORT = os.getenv('DATABASE_PORT')


BASE_DIR = os.path.dirname(os.path.dirname(__file__))

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME':  NAME,
        'USER':  USER,
        'PASSWORD': PASSWORD,
        'HOST':  HOST,
        'PORT':  PORT,
    }
}
