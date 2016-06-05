#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-05 19:24:21 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
登陆XUPT的教务处
1. 登陆首页，获得cookie
2. 找到表单的目的网址
3. 找到验证码的目的网址
"""

import os
import urllib
import urllib2
import cookielib

url = 'http://222.24.62.120/'


# 创建一个cookie实例
cookie = cookielib.CookieJar()
handler = urllib2.HTTPCookieProcessor(cookie)
opener = urllib2.build_opener(handler)


# 发送请求，获得首页
response = opener.open(url)


# 获取验证码，发送请求时要带上cookie，否则得到的验证码与当前会话没有联系
# 这里的验证码由人工输入
img_src = url + 'CheckCode.aspx'
with open('img.aspx', 'w+b') as img:
	img.write(opener.open(img_src).read())



# POST携带的数据，构建Request对象时一定要对携带的数据编码
data = {}
data['txtUserName'] = os.getenv('LOGIN_NAME')
data['TextBox2'] = os.getenv('LOGIN_PASSWD')
data['txtSecretCode'] = raw_input("请输入验证码:")
data['RadioButtonList1'] = '学生'
data['__VIEWSTATE'] = 'dDwyODE2NTM0OTg7Oz5LUCaVfG1Oi+QaOSKH9UZrpjfn1w=='
data['Button1'] = ''
data['lbLanguage'] = ''
data['hidPdrs'] = ''
data['hidsc'] = ''


# 请求首部
headers={}
headers['User-Agent'] = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:46.0) Gecko/20100101 Firefox/46.0'
headers['Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
headers['Accept-Language'] = 'en-US,en;q=0.5'
headers['Content-Type'] = 'application/x-www-form-urlencoded'


# 向服务器发送登陆请求
des_url = url + 'default2.aspx'
request = urllib2.Request(des_url, data=urllib.urlencode(data), headers=headers)
response = opener.open(request)


with open('stuinfo.html', 'w+b') as f:
	f.write(response.read())