# 简单博客搭建
***
[参考](https://github.com/Andrew-liu/my_blog_tutorial)

## 创建项目
$ django-admin startproject SimpleBlog
生成目录:
strawberry/
         |----README.md
         |----requirements.txt
         |----manage.py
         |----strawberry/
                        |----__init__.py
                        |----settings.py
                        |----urls.py
                        |----wsgi.py


## 项目所需第三方库
requirements.txt内容:
    Django==1.10.2
    Markdown==2.5.2
    Pygments==2.0.1
    bootstrap-admin==0.3.3
    dj-database-url==0.3.0
    dj-static==0.0.6
    django-markdown==0.8.4
    django-toolbelt==0.0.1
    gunicorn==19.1.1
    markdown2==2.3.0
    psycopg2==2.5.4
    static3==0.5.1
    pytz==201504
安装这些库:$ pip install -r requirements.txt

## 创建应用,更新文件目录
$ python manage.py startapp article
strawberry/
         |----README.md
         |----requirements.txt
         |----manage.py
         |----strawberry/
         |              |----__init__.py
         |              |----settings.py
         |              |----urls.py
         |              |----wsgi.py
         |              |----local_setting.py    # 数据库配置
         |----article/
         |           |----__init__.py
         |           |----admin.py
         |           |----apps.py
         |           |----models.py
         |           |----tests.py
         |           |----views.py
         |           |----templatetags/
         |           |              |---__init__.py
         |           |              |---custom_markdown.py   # 实现markdown功能
         |----templates/
         |           |---base.html
         |           |---home.html

## 数据库配置
修改环境变量:$ sudo vim /etc/profile
在配置文件的最后添加
`
export DATABASE_NAME=****
export DATABASE_USER=****
export DATABASE_PASSWORD=******
export DATABASE_HOST=******
export DATABASE_PORT=****
`

使环境变量生效: $ source /etc/profile


# 开始Django之旅
***
学习要点:
    * 自定义一个模板变量过滤器,如markdown功能
    * 中间件功能的实现
    * 部署Django的应用

## 1.数据库配置完善
***
修改strawberry/strawberry/local_setting.py文件:
将local_setting中的配置导入strawberry/strawberry/settings.py中,


## 2.安装应用
***
$ python manage.py startapp article
在strawberry/strawberry/settings.py中安装应用

将安装的应用都写入数据库
$ python manage.py migrate
+----------------------------+
| Tables_in_strawberry       |
+----------------------------+
| auth_group                 |
| auth_group_permissions     |
| auth_permission            |
| auth_user                  |
| auth_user_groups           |
| auth_user_user_permissions |
| django_admin_log           |
| django_content_type        |
| django_migrations          |
| django_session             |
+----------------------------+


## 3.使启动Django server
***
$ python manage.py runserver
在浏览器中输入localhost:8000/,出现It worked!,表示成功


## 4.管理后台将内容输入完成
***
因为是写一个博客站点,所以主角是博客,将博客映射成一个对象,则:
class Artical:
    1. blog_title: 在呈现时题头
    2. blog_preview: 预览文字
    3. blog_read: 浏览量
    4. blog_category: 分类
    5. blog_datetime: 日期
    6. blog_picture: 图片
    7. blog_love: 点赞
    8. blog_comment: 评论
    9. blog_reward: 打赏
    10. blog_text: 正文

定义一个Model,修改strawberry/article/models.py文件
class Artical(models.Model):
    ...
