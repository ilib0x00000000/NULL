#!/usr/bin/env  python
# -*- coding:utf-8 -*-


'''
使用urllib2库构造GET请求
GET请求携带的数据是直接接到url的后面的，所以只要对携带的数据进行编码，
然后拼接到url的后面即可
GET request：
	URL
	headers
	cookie
'''

import os
import urllib
import urllib2
import cookielib


## 准备request
# 请求的url
url = 'http://222.24.62.120/'

# 请求携带的参数
values = {}
data = urllib.urlencode(values)

# 请求的头部
headers = {}
headers["Accept"]          = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
headers["Accept-Encoding"] = "deflate, sdch"
headers["Accept-Language"] = "zh-CN,zh;q=0.8"
headers["Cache-Control"]   = "max-age=0"
headers["Connection"]      = "keep-alive"
headers["Host"]            = "cuiqingcai.com"
headers["Upgrade-Insecure-Requests"] = "1"
headers["User-Agent"]      = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"


## 构建GET request
request = urllib2.Request(url+'?%s' % data, headers=headers)


## 发送request
response = urllib2.urlopen(request, timeout=10)



def crawler_xupt():
	'''使用cookie爬学校正方教务
	'''
	url = 'http://222.24.62.120/'
	
	# 构造request
	request = urllib2.Request(url, headers=headers)

	# 设置cookie
	cookie  = cookielib.CookieJar()
	handler = urllib2.HTTPCookieProcessor(cookie)
	opener  = urllib2.build_opener(handler)
	urllib2.install_opener(opener)

	# 发送request
	# 正常响应之后就可以拿到cookie
	response = urllib2.urlopen(request, timeout=30)


	# 得到cookie然后发送请求得到图片
	picurl = url + 'CheckCode.aspx'
	request = urllib2.Request(picurl, headers=headers)

	response = urllib2.urlopen(request, timeout=30)
	with open('tmp.aspx', 'w') as f:
		f.write(response.read())

	code = raw_input('请输入验证码: ')

	## 构造新request，向首页中的表单提交页面发送请求
	# 表单要提交的内容，数据从浏览器中获取
	values = {}
	values['txtUserName'] = os.getenv(username)
	values['TextBox2']    = os.getenv(password)
	values['txtSecretCode'] = code
	values['__VIEWSTATE'] = 'dDwyODE2NTM0OTg7Oz5LUCaVfG1Oi+QaOSKH9UZrpjfn1w=='
	values['Button1']     = ''
	values['lbLanguage']  = ''
	values['hidPdrs']     = ''
	values['hidsc']       = ''
	data = urllib.urlencode(values)

	request = urllib2.Request(url, data=data, headers=headers)

	response = urllib2.urlopen(request, timeout=30)

	with open('text.html', 'w') as f:
		f.write(response.read())


if __name__ == '__main__':
	crawler_xupt()


'''
利用GET向server发送请求：
1. GET请求由4部分组成
	1. url
	2. data----向server传递的参数
	3. headers
	4. cookie

2. 发送请求

总结：构造请求---------->发送请求

url = ''

values = {}
values[key] = value
data = urllib.urlencode(values)

headers = {}
headers[key] = value

# 构建request
request = urllib2.Request(url+'?'+data, headers=headers)

# 准备cookie
cookie  = cookie.CookieJar()
handler = urllib2.HTTPCookieProcessor(cookie)
opener  = urllib2.build_opener(handler)
urllib2.install_opener(opener)


# 发送请求，当响应请求时，cookie就会自动从响应中获取
response = urllib2.urlopen(request, timeout=60)
'''