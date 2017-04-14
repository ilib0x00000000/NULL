# -*- coding:utf-8 -*-

#http://www.jianshu.com/p/3debfb110ad9#
#http://www.open-open.com/lib/view/open1490925322705.html


import re
import time
import json
import urllib
import urllib2
import cookielib


def _get_xsrf(text):
    get_xsrf_pattern = re.compile(r'<input type="hidden" name="_xsrf" value="(.*?)"')
    _xsrf = re.findall(get_xsrf_pattern, text)[0]
    return _xsrf



def crawler_zhihu(account, password):
    '''
    '''
    headers = {}
    headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
    headers["Accept-Encoding"] = "deflate, sdch"
    headers["Accept-Language"] = "zh-CN,zh;q=0.8"
    headers["Cache-Control"] = "max-age=0"
    headers["Connection"] = "keep-alive"
    headers["Upgrade-Insecure-Requests"] = "1"
    headers[
        "User-Agent"] = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36"


    # 1. GET index.html 获取_xsrf和cookies
    index_url = 'http://www.zhihu.com'

    # 构造request
    request = urllib2.Request(index_url, headers=headers)

    # 设置cookie
    cookie = cookielib.CookieJar()
    handler = urllib2.HTTPCookieProcessor(cookie)
    opener = urllib2.build_opener(handler)
    urllib2.install_opener(opener)

    # 发送request
    # 正常响应之后就可以拿到cookie
    response = urllib2.urlopen(request, timeout=30)
    _xsrf = _get_xsrf(response.read().decode('utf-8'))

    with open('index.html', 'wb') as f:
        f.write(response.read())

    t = str(int(time.time() * 1000))
    captcha_url = ''.join(['http://www.zhihu.com/captcha.gif?r=', t, "&type=login"])
    request = urllib2.Request(captcha_url, headers=headers)

    response = urllib2.urlopen(request, timeout=30)
    with open('captcha.gif', 'wb') as f:
        f.write(response.read())

    login_url = "https://www.zhihu.com/login/phone_num"

    # 知乎登录时发送的数据
    values = {}
    values['_xsrf'] = _xsrf
    values['phone_num'] = account
    values['password'] = password
    values['captcha'] = raw_input()
    data = urllib.urlencode(values)

    request = urllib2.Request(login_url, data=data, headers=headers)
    response = urllib2.urlopen(request, timeout=30)

    print json.loads(response.read().encode('utf-8'))['msg']


    with open('login.html', 'wb') as f:
        f.write(response.read())


    home_url = 'https://www.zhihu.com/#signin'


    request = urllib2.Request(home_url, headers=headers)
    response = urllib2.urlopen(request, timeout=30)
    with open('profile.html', 'wb') as f:
        f.write(response.read())

if __name__ == '__main__':
    crawler_zhihu('xxxxxxxxxxx', 'xxxxxxxxxxxxxxx')