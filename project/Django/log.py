#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
Python的logging配置由4个部分组成
Loggers
Handlers
Filters
Formatters

日志的等级
	DEBUG    用于调试目的的底层系统信息
	INFO     普通的系统信息
	WARNING  表示出现一个较小的问题
	ERROR    表示出现一个较大的问题
	CRITICAL 表示出现一个致命的问题

Loggers
Logger为日志系统的入口，每个logger命名都是bucket，可以向这个bucket写入需要处理的消息
写入logger的每条消息都是一个日志记录。
当一条消息传递给logger时，消息的日志级别将与logger的日志级别进行比较。如果消息的日志级别大于等于logger的日志级别，该消息将会往下继续处理。
如果小于，该消息将被忽略。
Logger一旦决定消息需要处理，它将传递该消息给一个Handler

Handlers
Handler决定如何处理logger中的每条消息。它表示一个特定的日志行为，例如将消息写到屏幕上、写到文件中或者是网络socket。
与Logger一样，handler也有一个日志级别。如果消息的日志级别小于handler的级别，handler将忽略该消息。
Logger可以有多个handler，而每个handler可以有不同的日志级别。利用这种方式，可以根据消息的重要性提供不同形式的处理。

Filters
Filter用于对从logger的日志记录进行额外的控制
默认情况下，满足日志级别的任何消息都将被处理。通过安装一个filter，可以对日志处理添加额外的条件。例如，安装一个filter，只允许处理来自特定源的ERROR消息
filter可以安装在Logger上或者handler上，多个filter可以串联起来实现多层filter行为

Formatter
最后，日志记录需要转换成文本。formatter表示文本的格式。

logging调用：
	* logger.debug()
	* logger.info()
	* logger.warning()
	* logger.error()
	* logger.critical()
"""


import logging
import datetime

# 1. 现在settings文件中定义日志文件配置
LOGGING = {
    'version': 1,
    'disable_existing_loggers': False,
    'formatters': {
        'line': {
            'format': '%(module)s %(message)s'
        }
    },
    'filters': {},
    'handlers': {
        'file_error': {
            'level': 'ERROR',
            'class': 'logging.FileHandler',
            'filename': '/var/log/django/error.log',
            'formatter': 'line',
        },
        'file_access': {
            'level': 'DEBUG',
            'class': 'logging.FileHandler',
            'filename': '/var/log/django/access.log',
        },
    },
    'loggers': {
        'log_error': {
            'handlers': ['file_error'],
            'level': 'ERROR',
            'propagate': True,
        },
        'log_access': {
            'handlers': ['file_access'],
            'level': 'DEBUG',
            'propagate': True,
        },
    },
}


# 2. 在需要引用日志功能的views文件中调用日志功能
logger = logging.getLogger('log_access')

logger.debug('this is a message %s' % datetime.datetime.now())
