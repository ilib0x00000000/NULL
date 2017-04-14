# -*- coding:utf-8 -*-

'''模拟微博登录
参考链接：
    http://www.jianshu.com/p/816594c83c74
    http://www.tuicool.com/articles/uIJzYff
'''

import re
import os
import rsa
import time
import base64
import urllib
import urllib2
import binascii
import cookielib

# 预登录的URL
# su的值是用户名经过base64编码的值


# 设置cookie
cookie  = cookielib.CookieJar()
handler = urllib2.HTTPCookieProcessor(cookie)
opener  = urllib2.build_opener(handler)
urllib2.install_opener(opener)
# cookie_filename = 'cookie_weibo.txt'
# cookie = cookielib.MozillaCookieJar()
# cookie.load(cookie_filename, ignore_discard=True, ignore_expires=True)
# handler = urllib2.HTTPCookieProcessor(cookie)
# opener = urllib2.build_opener(handler)

#**********************************************************设置代理***********************************************************#
# 注意这里的代理是否可用
# proxy_ip = "122.228.179.178"
# proxy_port = 80
# proxy = {'http': '%s:%s' % (proxy_ip, proxy_port)}
# proxy_handler = urllib2.ProxyHandler(proxy)
# opener = urllib2.build_opener(proxy_handler)
# urllib2.install_opener(opener)
#****************************************************************************************************************************#
	


def prelogin(username):
	'''在预登录时，会发送GET请求且携带一串数据
	entry:weibo
	callback:sinaSSOController.preloginCallBack
	su:xxxxxxxxxxxxxxxxxxxxxxxx
	rsakt:mod
	checkpin:1
	client:ssologin.js(v1.4.18)
	_:1492000339470
	'''
	# url
	prelogin_url = "https://login.sina.com.cn/sso/prelogin.php"

	# headers
	headers = {}
	headers["Accept"]          = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
	headers["Accept-Encoding"] = "deflate, sdch"
	headers["Accept-Language"] = "zh-CN,zh;q=0.8"
	headers["Cache-Control"]   = "max-age=0"
	headers["Connection"]      = "keep-alive"
	headers["Upgrade-Insecure-Requests"] = "1"
	headers["User-Agent"]      = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"

	# data
	values = {}
	values["entry"] = "weibo"
	values["rsakt"] = "mod"
	values["callback"] = "sinaSSOController.preloginCallBack"
	values["checkpin"] = "1"
	values["client"] = "ssologin.js(v1.4.18)"
	values["_"] = str(time.time() * 1000)
	values["su"] = base64.encodestring(username)  # base64加密后的用户名
	data = urllib.urlencode(values)


	# 构建request
	request = urllib2.Request(prelogin_url + '?%s' % data, headers=headers)

	# 发送request
	response = urllib2.urlopen(request, timeout=30)

	return eval(response.read().replace("sinaSSOController.preloginCallBack", ''))

'''
response属性
	close
	code
	fileno
	fp
	getcode
	geturl
	headers
	info
	msg
	next
	read()
	readline()
	readlines()
	url
'''


def login(username, password):
	'''登录时携带的数据
	entry:weibo
	gateway:1
	from:
	savestate:7
	useticket:1
	pagerefer:http://login.sina.com.cn/sso/logout.php?entry=miniblog&r=http%3A%2F%2Fweibo.com%2Flogout.php%3Fbackurl%3D%252F
	vsnf:1
	su:xxxxxxx
	service:miniblog
	servertime:1492004363
	nonce:9XAURD
	pwencode:rsa2
	rsakv:xxxxxxxx
	sp:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	sr:1440*900
	encoding:UTF-8
	prelt:38
	url:http://weibo.com/ajaxlogin.php?framelogin=1&callback=parent.sinaSSOController.feedBackUrlCallBack
	returntype:META
	'''
	prelogin_return_data = prelogin(username)

	# url
	login_url = "http://login.sina.com.cn/sso/login.php"

	# headers
	headers = {}
	headers["Accept"]          = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
	headers["Accept-Encoding"] = "deflate, sdch"
	headers["Accept-Language"] = "zh-CN,zh;q=0.8"
	headers["Cache-Control"]   = "max-age=0"
	headers["Connection"]      = "keep-alive"
	headers["Upgrade-Insecure-Requests"] = "1"
	headers["User-Agent"]      = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"

	# data
	values = {}
	values['entry'] = "weibo"
	values['gateway'] = "1"
	values['from'] = ""
	values['savestate'] = "7"
	values['useticket'] = "1"
	values['pagerefer'] = "http://login.sina.com.cn/sso/logout.php?entry=miniblog&r=http%3A%2F%2Fweibo.com%2Flogout.php%3Fbackurl%3D%252F"
	values['vsnf'] = "1"
	values['service'] = "miniblog"
	values['pwencode'] = 'rsa2'
	values['sr'] = '1440*900'
	values['encoding'] = 'UTF-8'
	values['url'] = "http://weibo.com/ajaxlogin.php?framelogin=1&callback=parent.sinaSSOController.feedBackUrlCallBack"
	values['returntype'] = "META"


	# 根据预登录返回值改变的数据
	values['su'] = base64.encodestring(username)
	values['prelt'] = 38
	values['servertime'] = prelogin_return_data['servertime']
	values['nonce'] = prelogin_return_data['nonce']
	values['rsakv'] = prelogin_return_data['rsakv']

	# 处理密码加密
	pubkey = prelogin_return_data['pubkey']
	rsaPublickey = int(pubkey, 16)
	key = rsa.PublicKey(rsaPublickey, 65537)
	passwd = rsa.encrypt(''.join([str(prelogin_return_data['servertime']), '\t', prelogin_return_data['nonce'], '\n', password]).encode('utf-8'), key)
	values['sp'] = binascii.b2a_hex(passwd)


	data = urllib.urlencode(values)

	# request
	request = urllib2.Request(login_url, headers=headers, data=data)

	# 发送request
	response = urllib2.urlopen(request, timeout=60)



	# 匹配出跳转的URL
	# http://passport.weibo.com/wbsso/login?ssosavestate=1523677710&url=http%3A%2F%2Fweibo.com%2Fajaxlogin.php%3Fframelogin%3D1%26callback
	# %3Dparent.sinaSSOController.feedBackUrlCallBack&ticket=ST-NTMwOTI0NTQ2OQ==-1492141710-tc-73B3EAF4EC56EF054E3C8A650FA4DF4C-1&retcode=0
	pattern = r"replace\(\'(.*?)\'\)"
	regex = re.compile(pattern, re.UNICODE)
	match = regex.findall(response.read().decode("GBK"))
	if match:
		finally_url = match[0]
		print finally_url


		request = urllib2.Request(finally_url, headers=headers)
		response = urllib2.urlopen(request, timeout=30)
		# 这里的重定向，urllib已经自动处理了


		pattern = r"feedBackUrlCallBack\((.*?)\)"
		regex = re.compile(pattern, re.UNICODE)
		match = regex.findall(response.read())
		if match:
			true = True
			null = None
			resdata = eval(match[0])
			uniqueid = resdata['userinfo']['uniqueid']
			print uniqueid
			# 最终要获取的uniqueid

			# print response.read()
			# uniqueid
			# <html><head><script language='javascript'>parent.sinaSSOController.feedBackUrlCallBack(
			# 	{"result":true,"userinfo":{"uniqueid":"xxxxxx","userid":null,"displayname":null,
			# 	"userdomain":"?wvr=5&lf=reg"},"redirect":"http:\/\/weibo.com\/nguide\/interest"});
			# 	</script></head><body></body></html>

			# print response.code
			# print response.geturl()
			# print response.info()
			# print response.info().getheader("Location")	
					
			login_done_url = "http://weibo.com/u/%s/home" % uniqueid
			request = urllib2.Request(login_done_url, headers=headers)
			response = urllib2.urlopen(request, timeout=60)

			# if response.code == 200:
			# 	with open("index.html", "wb") as f:
			# 		f.write(response.read())
			# else:
			# 	with open("error.html", "wb") as f:
			# 		f.write(response.read())
			

			# cookie使用参见：https://docs.python.org/2/library/cookielib.html#cookielib.CookieJar
			for item in cookie:
				print item.name , item.value

		else:
			print 'error2....'
	else:
		print 'error1....'

if __name__ == '__main__':
	response = login("xxxxxxxx", "xxxxxxxxxxxxxxxxxxxxxx")


'''
sinaSSOController.preloginCallBack(
	{
		"retcode":0,
		"servertime":1492001496,
		"pcid":"tc-0d07577c888eb10da3ee431265d5d2245594",
		"nonce":"1Y9L2V",
		"pubkey":"xxxxxxxxxxxxxxxxxxxxxxxxx",
		"rsakv":"1330428213",
		"is_openlock":0,
		"lm":1,
		"smsurl":"https:\/\/login.sina.com.cn\/sso\/msglogin?entry=weibo&mobile=15829208975&s=3d90c2f3f84de512bad253e34b6b813c",
		"showpin":0,
		"exectime":9
	}
)

<html>
	<head>
		<script language='javascript'>parent.sinaSSOController.feedBackUrlCallBack(
			{
				"result":true,
				"userinfo":{
					"uniqueid":"......",
					"userid":null,
					"displayname":null,
					"userdomain":"?wvr=5&lf=reg"
				},
				"redirect":"http:\/\/weibo.com\/nguide\/interest"
			}
		);
		</script>
	</head><body></body></html>
'''







