# Web
***
[Python+Apache搭建server](http://blog.csdn.net/edhroyal/article/details/9423803)
[参考](http://blog.csdn.net/ggicci/article/details/8203222)

Server version: Apache/2.4.7 (Ubuntu)

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


## 视图views

## URLconf

## 模板template


## MVC
## MTV

## 创建一个应用
[参考](http://blog.chinaunix.net/uid-29578485-id-5751415.html)
注意：
    在v1.10.1之前的settings.py中的INSTALLED_APPS添加一个应用时:'site.app_name'
    在v1.10.1之后的settings.py中的INSTALLED_APPS添加一个应用时:'app_name'

添加应用之后检查一下是否有错误
v1.10.1+:$ python manage.py check
v<1.10.1:$ python manage.py validate

## M(Model)模型
[Django模型---数据库模块](http://www.cnblogs.com/pycode/p/db-middleware.html)




## 站点管理--admin


## Request对象
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
[参考](http://www.tuicool.com/articles/qMzUnq)



## FORM类
Django带有一个form库，称为django.forms
可以为HTML中的每个form创建一个Form对象，该对象继承于forms.Form

Django的forms框架可以处理：
    * HTML显示
    * 数据校验
    * 数据清理
    * 表单错误重现

Form的field类表现校验逻辑
组件(widget)表现显示逻辑

当为表单创建一个类后，除了在创建时可以调用Django自带的校验方式，也可以编写自定义的数据字段校验方式

## 部署Django
***

## 其他链接
[Django在线教程](http://www.ziqiangxuetang.com/django/django-deploy.html)



