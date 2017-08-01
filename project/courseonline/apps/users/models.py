# -*- coding:utf-8 -*-

from __future__ import unicode_literals
from datetime import datetime

from django.db import models
from django.contrib.auth.models import AbstractUser

# Create your models here.


class UserProfile(AbstractUser):
    nick_name = models.CharField(max_length=50, null=True, blank=True, verbose_name='昵称', default='')
    birthday  = models.DateField(verbose_name='生日', null=True, blank=True)
    gender    = models.CharField(max_length=6, choices=(('male', '男'), ('female', '女')), default='male')
    address   = models.CharField(max_length=100, default='')
    mobile    = models.CharField(max_length=11, null=True, blank=True)
    has_active = models.BooleanField(default=False, verbose_name='是否激活')
    image     = models.ImageField(upload_to='image/%Y/%m', default='image/default.jpg')

    class Meta:
        verbose_name = '用户信息'
        verbose_name_plural = verbose_name

    def get_unread_message_num(self):
        from operation.models import UserMessage
        return UserMessage.objects.filter(user=self.id, has_read=False).count()

    def __unicode__(self):
        return self.username

    __str__ = __unicode__


class EmailVerifyRecond(models.Model):
    code = models.CharField(max_length=20, verbose_name='验证码')
    email = models.EmailField(max_length=50, verbose_name='邮箱')
    send_type = models.CharField(max_length=10, choices=(('register', '注册'), ('forget', '忘记密码'), ('update', '更新密码')), verbose_name='邮箱类型')
    send_time = models.DateTimeField(default=datetime.now, verbose_name='注册时间')

    class Meta:
        verbose_name = '邮箱'
        verbose_name_plural = verbose_name

    def __unicode__(self):
        return self.email

    __str__ = __unicode__


class Banner(models.Model):
    title = models.CharField(max_length=100, verbose_name='标题')
    image = models.ImageField(upload_to='banner/%Y/%m', verbose_name='轮播', max_length=100)
    url = models.URLField(max_length=200, verbose_name='访问地址')
    index = models.IntegerField(default=100, verbose_name='顺序')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = '轮播'
        verbose_name_plural = verbose_name

    def __unicode__(self):
        return self.title

    __str__ = __unicode__















