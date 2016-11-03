# Web
***
[Python+Apache搭建server](http://blog.csdn.net/edhroyal/article/details/9423803)
[参考](http://blog.csdn.net/ggicci/article/details/8203222)
[Django1.5中文版教程：](https://django-chinese-docs.readthedocs.io/en/latest/intro/index.html)
	https://github.com/7sDream/django-intro-zh

[Django项目----搭博客：](http://www.jianshu.com/p/3bf9fb2a7e31#)

Server version: Apache/2.4.7 (Ubuntu)

下载Apache: sudo apt-get install apache2

启动Apache： /etc/init.d/apache2 start
Apache配置文件：/etc/apache2/apache2.conf    
                /etc/apache2/conf-enabled  
                /etc/apache2/magic           
                /etc/apache2/mods-enabled  
                /etc/apache2/sites-available
                /etc/apache2/conf-available  
                /etc/apache2/envvars       
                /etc/apache2/mods-available  
                /etc/apache2/ports.conf    
                /etc/apache2/sites-enabled

配置Apache：
    1. 修改/etc/apache2/ports.conf -----> 端口改为8080
    2. 修改/etc/apache2/apache2.conf -----> 添加
        ServerName localhost
    3. 给apache的日志文件权限
        sudo chmod 777 /var/log/apache2/*
    4. 启动Apache:
        sudo /etc/init.d/apache2 start


中间件：用于在Web服务器和Web应用之间添加额外的功能
中间件要么对来自用户的数据进行预处理，然后发送给应用
要么将响应负载返回给用户之前，对结果数据进行一些最终的调整

预处理可以包括动作，如拦截、修改、添加、移除请求参数，修改环境变量，使用URL路径分派应用的功能，转发或重定向请求，通过入站客户端IP地址对网络流量进行负载平衡，委托其功能，以及其他功能。


会话管理：一段时间内在一个或多个请求之间保存用户的状态。一般来说，这是通过某种形式的持久存储完成的，如缓存、平面文件甚至是数据库


## Web服务器：
BaseHTTPServer   用来开发Web服务器的抽象类
SimpleHTTPServer 处理最简单的HTTP请求
CGIHTTPServer    既能像SimpleHTTPServer一样处理Web文件，又能处理CGI请求
http.server      Python3中BaseHTTPServer、SimpleHTTPServer和CGIHTTPServer模块的
                 组合包
wsgiref          WSGI参考模块

# Web框架---[Django](http://djangobook.py3k.cn/2.0/)
***
* Django
* OAuth
* ORM(对象关系映射)
* 底层数据库适配
* 单元测试
* 持续集成框架


### 安装Django
$ sudo pip install Django

### 测试Django版本
$ python -m django --version

#### 项目
项目就是一些列文件，用来创建并运行一个完整的Web站点

#### 应用
在项目文件夹下，有一个或多个子文件夹，每个子文件夹有特定的功能，称为应用


Python第三方库安装路径：
/usr/local/lib/python2.7/dist-packages/


## 创建一个项目
$ django-admin startproject folder_name
folder_name/ ----
                |
                |----folder_name/----
                |                   |----__init__.py   告诉Python这是一个软件包
                |                   |----settings.py   全局URL配置
                |                   |----urls.py       项目相关的配置
                |                   |----wsgi.py       应用的命令行接口
                |
                |------manage.py

## 启动一个Django Server
$ python manage.py runserver

## Django运行时动态
1. 启动server： $ python manage.py runserver
2. 脚本(manage.py)去寻找setting.py的文件，这个文件包含了Django项目的配置信息
   TEMPLATE_DIRS
   DATABASE_NAME
   ROOT_URLCONF : 指明Django项目的url映射的文件------> localsite.urls
3. 当有一个请求要求访问某个文件时，Django会根据ROOT_URLCONF的设置装载URLconf,然后按顺序逐个匹配URLconf里的URLpatterns，直到找到一个匹配的，然后调用相应的view函数。
4. 对应的view函数的第一个参数是HttpRequest对象
5. view函数返回一个HttpResponse对象
6. Django将HttpResponse对象转换成一个合适的HTTP response，以Web page显示出来


## M(Model)模型
***
模型（model）：[参考](http://www.jianshu.com/p/32a8a06da678#)
[Django模型---数据库模块](http://www.cnblogs.com/pycode/p/db-middleware.html)
* 确保数据库安装配置好
* 确保python-mysql库安装好

1. 数据库配置
	settings.py
        'ENGINE'   
        'NAME'    
        'USER'     
        'PASSWORD'
        'HOST'    
        'PORT'     

2. 创建应用APP
	$ python manage.py startapp book(app_name)
	在settings.py中的INSTALLED_APPS中添加应用
	book/
		|----__init__.py
		|----models.py
		|----tests.py
		|----views.py
        |----apps.py
        |----admin.py
        |----migrations/
                    |-----__init__.py

3. 创建模型
	django.db.models模块
	在book/models.py中创建模型
	class ModelDemo(models.Model):
		name    = models.CharField(max_length=30)
		address = models.CharField(max_length=50)
		city    = models.CharField(max_length=60)
		country = models.CharField(max_length=50)
		website = models.URLField()
		state_province = models.CharField(max_length=30)

4. 同步数据库(以下两步在修改模型配置后都必须执行)
	$ python manage.py makemigrations
	$ python manage.py migrate

5. 打开book/admin.py，写入一下内容：
	`
		from django.contrib import admin
		from .models import ModelDemo

		admin.site.register(ModelDemo)
	`

6. 创建管理员账户：
	$ python manage.py createsuperuser
	# 输入账户密码

7. 数据库的操作


## Django中数据库API调用
***
1. 根据应用中的models模块的模型定义,实例化出一个对象
2. 调用对象的save方法,将一条记录写入数据库
如果,在定义数据库的模型时,没有定义一个主键,Django会为每个模型自动添加一个主键id

例,在应用的models定义一个模型:
`
class ModelClass(django.db.models.Model):
    ...
`
注:为调试方便,每个Model对象都应该有一个__unicode__方法

向数据库写入记录:
    将记录写进数据库
    mc = ModelClass(...)
    mc.save()

    或:
    m = ModelClass.objects.create(...)

读取数据库的记录:
    读取所有数据: ModelClass.objects.all()
    筛选部分数据: ModelClass.objects.filter(...)
    查找单个数据: ModelClass.objects.get(...)
    对查询数据排序: ModelClass.objects.order_by()
    对查找到的数据更新: ModelClass.objects.get(...).update(...)
    删除一条数据: ModelClass.objects.delete()
    删除所有数据: ModelClass.objects.all().delete()


## 视图views
***
视图由一群函数组成:所有的函数的第一个参数都是HttpRequest对象,且返回一个HttpResponse对象
## URLconf
***
            request(HttpRequest)
                v
            settings(指定URLconf文件所在的位置)
                v
            urls(根据url映射的视图函数,调用对应的视图函数)
                v
            views(视图函数所在的文件,每个视图函数的第一个参数都是Request,且返回一个HttpResponse对象)
                v
            HttpResponse

总结:
    1. 有请求进来
    2. Django通过settings中的ROOT_URLCONF配置来决定根URLconf
    3. Django在URLconf中的所有模式中搜索到第一个匹配request url的条目
    4. 如果找到匹配,将调用相应的视图函数
    5. 视图函数返回一个HttpResponse对象
    6. Django将HttpResponse对象转换成一个适合的HTTP response,并返回

pro_name/
		|
		|---manage.py
		|
		|
		|---pro_name/
		|			|
		|			|---__init__.py    ()
		|			|---settings.py    (Django的配置文件)
		|			|---urls.py        (URLconf)
		|			|---wsgi.py        (部署Django时使用)
		|
		|---book/
		|		|
		|		|---__init__.py
		|		|---models.py
		|		|---tests.py
		|		|---views.py
		|		|---admin.py
		|		|---app.py
		|		|---urls.py
		|		|---template/
		|		|---static/
		|		|---migration/
		|					|
		|					|--__init__.py
		|
		|
		|---blog/
		|		|
		|		|---__init__.py
		|		|---models.py
		|		|---tests.py
		|		|---views.py
		|		|---admin.py
		|		|---app.py
		|		|---urls.py
		|		|---template/
		|		|---static/
		|		|---migration/
		|					|
		|					|--__init__.py
		|		
		|
		|---other_app/
		|			|
		|			|---__init__.py
		|			|---models.py
		|			|---tests.py
		|			|---views.py
		|			|---admin.py
		|			|---app.py
		|			|---urls.py
		|			|---template/
		|			|---static/
		|			|---migration/
		|						|
		|						|--__init__.py


URLconf:
1. URL直接映射view视图函数
`
	from book import view
	urlpatterns = [
		(r'^$',   view.func),
		(r'book/list', view.list),
	]
`
2. URL映射的是完整的函数路径字符串
`
	urlpatterns = [
		(r'^$', 'book.view.func'),
		(r'books', 'book.view.list'),
		(r'blogs', 'blog.view.list'),
	]
`
3. URL中使用命名正则表达式
`
	urlpatterns = [
		(r'book/(?p<name>.*?)', book.view.query),		# query接受一个查询书名的参数name
		(r'blog/(?p<subject>.*?)', blog.view.all),		# all函数接受一个叫subject的参数
	]
`
4. URL映射中传递指定变量
`
	urlpatterns = [
		(r'book/\w+', book.view.query, {'name':'head first'}),		# query函数中会接受一个name关键字参数
		(r'blog/\w+', blog.view.query, {'subject':'python'}),		# query函数中会接受一个subject关键字参数
	]
`
5. URL映射中集成APP的URLconf
`
	urlpatterns = [
		(r'^book/', include('pro_name.book.urls')),		# 根URLconf会将请求url截掉/book/之后传递给pro_name/book/urls.py中的URLconf
		(r'^blog/', include('pro_name.blog.urls')),		# 根URLconf会将请求url截掉/blog/之后传递给pro_name/blog/urls.py中的URLconf
	]
`

URLconf注意事项：
	* 如果在一个url映射中同时使用命名正则和字典参数，且两者的变量名冲突，则优先使用字典参数
	* 越特殊的url（需要单独处理的）要放在URLconf的最上面
	* 根URLconf在向应用的URLconf传递url时，是会先把根URLconf中的部分截掉的



## 模板Template
***
    * 模板变量
    * 模板标签
    * 过滤器

#### 模板的使用
    1. 可以用原始的模板字符串创建一个Template对象,Django同样支持用指定模板文件路径的方式来创建Template对象
    2. 调用模板对象的render方法,并且传入一套变量context,他将返回一个基于模板的展现字符串,模板中的变量和标签会被context值替换

注:实例化一个Template对象时,可能会抛出django.template.TemplateSyntaxError异常

    1. 写模板
    2. 创建Template对象
    3. 创建Context对象
    4. 调用render方法

一个模板可以由多个Context对象渲染,只进行一次Template对象的实例化,多次调用render方法渲染.

模板中的变量也可以使用字典/对象,只要传递的关键字与模板中的变量名相同即可,查找顺序如下:
    * {{ var.name }}  var是一个字典,name是字典的一个键
    * {{ var.year }}  var是一个对象,year是对象的属性
    * {{ var.upper }} var是一个对象,upper是对象的方法
    * {{ var.2 }}     var是一个列表,2是列表的下标

当模板中的变量调用方法时,如果该方法抛出一个异常,除非该异常有一个silent_variable_failure属性,且值为True,
否则异常将会被传播,如果异常被传播,模板里的指定变量会被置为空字符串

#### 模板标签for
属性:
    1. forloop.counter
    2. forloop.counter0
    3. forloop.revcounter
    4. forloop.revcounter0
    5. forloop.first--------布尔值
    6. forloop.last---------布尔值
    7. forloop.parentloop

#### 其他模板标签
{% if %}/{% else %}/{% endif %}
{% for in %}/{% endfor %}
{% ifequal %}/{% endifequal %}
{% ifnotequal %}/{% endifnotequal %}

#### 模板中的注释
单行注释: {# ... #}
多行注释: {% comment %}...{% endcomment %}

### 过滤器
模板过滤器:在变量被显示前修改它的值的一个简单方法,使用管道符
如果过滤器有参数,跟随冒号之后并且总是以双引号包含
{{ var|filter_function:"para1,para2" }}

### 模板加载
            request
                v
            django根据settings中的TEMPLATE_DIRS找到模板所在目录
                v
            view视图函数读取模板目录中的文件
                v
            返回一个HttpResponse对象

模板使用到的函数:
    django.template.Template()
    django.template.Context()
    django.template.loader.get_template()
    django.template.loader.select_template()
    django.shortcuts.render_to_response()

## 在view视图函数中使用模板
1. 设置模板文件所在的路径, settings中的TEMPLATES.DIRS
2. 加载模板文件get_template()/select_template()
3. 渲染模板文件,COntext(),调用render()函数
4. 返回Response


## Request对象
***
    URL信息：
        request.path:        除域名外的请求路径，以正斜杠开头
        request.get_host():  主机名
        request.get_full_path(): 请求路径，可能包含查询字符串
        request.is_secure(): 是否通过HTTPS访问

    META信息：
        request.META是一个Python字典，包含了请求的headers信息，例：
        request.META['HTTP_USER_AGENT']
        request.META['HTTP_REMOTE_ADDR']
        request.META['HTTP_ACCEPT_ENCODING']
        request.META['HTTP_ACCEPT']

        META是一个字典，当访问字典中的键但是键不存在时会触发异常

    GET对象：
        GET对象是一个类字典对象，包含了get请求携带的查询键值对，例：
        request.GET['name']
        request.GET['item']

    POET对象：
        POST对象是一个类字典对象，包含了POST请求携带的查询键值对，例：
        request.POST['username']
        request.POST['password']


## 表单
***
[参考](http://www.jianshu.com/p/5664dd79c0ba)
[参考](http://www.tuicool.com/articles/qMzUnq)
[参考](http://www.jianshu.com/p/7795783979da#)
## FORM类
Django带有一个form库，称为django.forms
可以为HTML中的每个form创建一个Form对象，该对象继承于forms.Form

Django的forms框架可以处理：
    * HTML显示
    * 数据校验
    * 数据清理
    * 表单错误重现

Form的field类表现校验逻辑
    * CharField()
    * DateField()
    * IntegerField()

    Field的构造参数:
        * Field.required
        * Field.label
        * Field.help_text
        * Field.error_messages
        * Field.widget
        * Field.max_length
        * Field.min_length

组件(widget)表现显示逻辑
    * forms.Select()
    * forms.TextInput()
    * forms.PasswordInput()
    * forms.NumberInput()
    * forms.EmailInput()
    * forms.URLInput()
    * forms.DateInput()
    * forms.DateTimeInput()
    * forms.CheckboxInput()
    * forms.RadioSelect()
    * forms.FileInput()

    widget组件的构造参数:
        * attrs

当为表单创建一个类后，除了在创建时可以调用Django自带的校验方式，也可以编写自定义的数据字段校验方式
在创建的form类中,为需要自定义校验方式的字段写一个函数,该函数是以clean_开头,后面是需要校验的字段名


创建一个form对象
`
class DefinedForm(django.forms.Form):
    ...
`

df = DefinedForm({...})

检查实例是否有效:
    df.is_valid()
如果实例是有错误的:
    df.errors
将Form提交的数据转成相应的Python数据:
    df.cleaned_data





## 部署Django
***


## 模板系统
***
* 使用Template/Context组合,Template创建一个带模板变量和模板标签的Template对象,Context创建一个关键字字典,
与模板中的变量/标签映射,最后调用t.render(c)返回一个相应
* 使用Template/RequestContext组合,当在构建一个Context对象时,有时需要使用request对象中的键值对,RequestContext
对象就是为了解决这个问题
* 使用render_to_response/RequestContext组合,更减少代码量



## 安装配置git
$ git --global....
$ git --global....
$ ...
$ ...
$ git clone https://github.com/ilib0x00000000/NULL.git
$ git remote add origin https://github.com/ilib0x00000000/NULL.git(如果这部失败,且提示仓库已存在)
	$ git remote rm origin
	$ git remote add origin https://github.com/ilib0x00000000/NULL.git
$ git add filename
$ git commit -m "..."
$ git push -u origin master

[参考](http://www.cnblogs.com/hzg1981/p/5899364.html)

## 异常
模板:
    TemplateSyntaxError
    TemplateDoesNotExist
数据库API:
    ModelClass.DoesNotExist

## 其他链接
[Django在线教程](http://www.ziqiangxuetang.com/django/django-deploy.html)\

[Atom插件推荐](https://www.zhihu.com/question/39938370)
