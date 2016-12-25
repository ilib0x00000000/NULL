#!/usr/bin/env  python
# -*- coding:utf-8 -*-


'''
封装发送邮箱设置
email模块负责构造邮件
smtplib模块负责发送邮件
'''

import os
import re
import sys
from smtplib import SMTP_SSL, SMTP
from email.header import Header
from email.mime.text import MIMEText

USERNAME    = '965838596@qq.com'
AUTHTOKEN   = os.getenv('QQ_EMAIL_AUTH_TOKEN') or 'xxxx'
SERVER_HOST = 'smtp.qq.com'               # QQ邮箱站点
SERVER_PORT = 465                         # QQ邮箱服务端口


def send_mail(sessions):
	'''向指定的用户发送邮箱
	参数：
		build_mail构造邮件之后，传递一个邮件列表，将根据sessions中的每个msg发送
	'''
	smtp = SMTP_SSL(SERVER_HOST, SERVER_PORT)
	smtp.set_debuglevel(1)
	smtp.ehlo(SERVER_HOST)
	smtp.login(USERNAME, AUTHTOKEN)

	for session in sessions:
		regex = re.compile(r'<(.+)>', re.UNICODE)
		from_addr = regex.search(session['From']).group(1)
		to_addr   = regex.search(session['To']).group(1)
		smtp.sendmail(from_addr, to_addr, session.as_string())

	smtp.quit()



def build_mail(from_addr, to_addr, subject, text, mailtype='plain'):
	'''构造一个完整的邮件，有主题，有发送人，有正文
	邮件主题、显示发件人、收件人信息并不是通过SMTP协议发送的，而是包含在发送的文本中
	'''
	from email import encoders
	from email.header import Header
	from email.mime.text import MIMEText

	msg = MIMEText(text, mailtype, 'utf-8')
	msg['From'] = _format_addr(from_addr)
	msg['To']   = _format_addr(to_addr)
	msg['Subject'] = Header(subject, 'utf-8').encode()

	return msg



def _format_addr(s):
	from email.utils import parseaddr
	from email.utils import formataddr
	name, addr = parseaddr(s)
	return formataddr(( \
		Header(name, 'utf-8').encode(),
		addr.encode('utf-8') if isinstance(addr, unicode) else addr))


if __name__ == '__main__':
	msg1 = build_mail('某某<12233333@qq.com>', '张三<2537829@qq.com>', 'test', 'hello world')
	msg2 = build_mail('某某<12233333@qq.com>', '张三<2537829@qq.com>', 'test', 'hello world')

	send_mail([msg1, msg2])
