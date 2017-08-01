# -*- coding:utf-8 -*-

"""courseonline URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.9/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url, include
import xadmin
from django.views.generic import TemplateView
from django.views.static import serve
from django.views.generic.base import RedirectView

from users.views import LoginView, RegisterView, ActiveView, UpdatePasswordView, ResetPasswordView
from courseonline.settings import MEDIA_ROOT
from core.views import LogoutView, IndexView

urlpatterns = [
    url(r'^$', IndexView.as_view(), name='index'),
    url(r'^index.html$', IndexView.as_view(), name='index_html'),
    url(r'^login.html$', LoginView.as_view(), name='login'),
    url(r'^logout$', LogoutView.as_view(), name='logout'),
    url(r'^register.html$', RegisterView.as_view(), name='register'),
    url(r'^active', ActiveView.as_view(), name='active'),
    url(r'^password/110$', UpdatePasswordView.as_view(), name='find_password'),
    url(r'^password/find', ResetPasswordView.as_view(), name='reset_password'),
    url(r'^favicon\.ico$', RedirectView.as_view(url='/static/img/favicon.ico')),

    url(r'^teacher/', include('operation.urls', namespace='teacher'), name='teacher'),
    url(r'^org/', include('orgzation.urls', namespace='org'), name='orglist'),
    url(r'^course/', include('courses.urls', namespace='course'), name='course'),
    url(r'^search/', include('core.urls', namespace='search'), name='core'),
    url(r'^user/', include('users.urls', namespace='user'), name='user'),
    url(r'^test/', include('tests.urls', namespace='test'), name='test'),

    # 后台管理
    url(r'^xadmin/', xadmin.site.urls),
    # 处理静态文件
    # url(r'^static/(?P<path>.*)', serve, {"document_root": STATIC_ROOT}),   # 在DEBUG为False时，且没有使用Apache/Nginx部署时，需要django处理静态文件的传输
    url(r'^media/(?P<path>.*)', serve, {"document_root": MEDIA_ROOT}),
    # 验证码插件
    url(r'^captcha/', include('captcha.urls'), name='captcha'),
    # 富文本相关URL
    url(r'^ueditor/', include('DjangoUeditor.urls')),
]


# 404处理页面
handler404 = 'core.views.response404'

# 500处理页面
handler500 = 'core.views.response500'

# 403处理页面
handler403 = 'core.views.response403'
