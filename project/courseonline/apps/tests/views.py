# -*- coding:utf-8 -*-

from django.shortcuts import render
from django.views.generic import View
from django.http import HttpResponse

"""
Web的安全
    1. SQL注入
    2. CSS攻击
    3. XSRF攻击
"""


class ErrorView(View):
    def get(self, request):
        print 1/0
        return render(request, '500.html', {})


class SQLView(View):
    def get(self, request):
        return render(request, 'login.html', {})

    def post(self, request):
        import MySQLdb

        username = request.POST.get('username', '')
        password = request.POST.get('password', '')
        conn = MySQLdb.connect(host='localhost', user='root', passwd='123456', db='course')
        cursor = conn.cursor()

        # " OR 1 = 1 ; #
        sql_string = 'select * from users_userprofile WHERE username="{0}" AND password="{1}"'.format(username, password)
        print sql_string
        result = cursor.execute(sql_string)
        print result

        for row in cursor.fetchall():
            print row

        return HttpResponse('.....')


class XSSView(View):
    """
    数据中包含js代码

    <script>x = document.cookie; alert(x); </script>
    可以使cookie与IP绑定
    """
    html = """
    <!DOCTYPE html>
    <html>
    <head>
        <title></title>
        <meta charset="utf-8">
    </head>
    <body>
    
    <form action="#">
        <input type="text" name="">
        <input type="text" name="">
        <input type="button" name="提交" value="提交">
    </form>
    
    </body>
    </html>
    """
    def get(self, request):
        return HttpResponse(self.html)

    def post(self, request):
        pass


class CSRFView(View):
    """
    跨站请求伪造

    防护方法：使用POST方法，加{% csrf_token %}
    """
    def get(self, request):
        pass

    def post(self, request):
        pass


from django.views.decorators.cache import cache_page


class CacheView(View):
    def get(self, request):
        import time
        return render(request, 'test1.html', {
            'time' : time.time(),
        })


@cache_page(3)
def cache(request):
    import time
    return render(request, 'test1.html', {
        'time': time.time(),
    })


def test_signal(request):
    from .models import UnitTestModel

    utm = UnitTestModel()
    utm.name = 'test'
    print '....'
    utm.save()
    print '****'

    # obj = UnitTestModel.objects.get(name='test')
    # print '---->'
    # obj.delete()
    # print '<----'

    return HttpResponse('ok')