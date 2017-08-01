# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/18 12:06
'''

import random
import smtplib

from email.header import Header
from email.mime.text import MIMEText

from users.models import EmailVerifyRecond
from courseonline.settings import EMAIL_HOST, EMAIL_HOST_USER, EMAIL_HOST_PASSWORD


def _code(length):
    '''
    产生随机数字
    :return:
    '''
    alpha = 'aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890'
    code = ''.join([random.choice(alpha) for i in xrange(length)])
    return code


# 邮件发送
def sendmail(recipients, subject, content):
    """
    :param recipients: 收件人邮箱
    :param subject:    主题
    :param content:    内容
    :return:
    """
    sender = EMAIL_HOST_USER  # 发件人邮箱
    password = EMAIL_HOST_PASSWORD  # 发件人邮箱密码
    host = EMAIL_HOST  # 发件人邮箱主机

    msg = MIMEText(content, 'plain', 'utf-8')
    msg['From'] = sender
    msg['To'] = recipients
    msg['Subject'] = Header(subject, 'utf-8').encode()

    server = smtplib.SMTP_SSL(host, 465)
    server.login(sender, password)
    server.sendmail(sender, [recipients], msg.as_string())
    server.quit()


def email_send(email, send_type='register', length=16):
    '''
    发送邮箱
    :param email:
    :param type:
    :return:
    '''
    rege = EmailVerifyRecond()

    rege.email = email
    rege.code = _code(length)
    rege.send_type = send_type

    content = {
        'update': ['【在线课堂教育】邮箱验证', '修改密码验证码：%s' % rege.code],
        'register' : ['【在线课堂教育】在线注册激活链接', '请点击如下链接，以激活账号： http://127.0.0.1:8000/active/?code=%s' % rege.code],
        'forget' : ['【在线课堂教育】重置密码', '请点击如下链接修改密码：http://127.0.0.1:8000/password/find/?code=%s' % rege.code],
    }

    rege.save()
    sendmail(email, content[send_type][0], content[send_type][1])
    return True


__all__ = [ email_send, _code ]

