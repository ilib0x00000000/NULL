# -*- coding:utf-8 -*-

from __future__ import unicode_literals

from django.db import models

# Create your models here.


class UnitTestModel(models.Model):
    name = models.CharField(max_length=20, verbose_name='用户名')

    class Meta:
        verbose_name = '测试用例'
        verbose_name_plural = verbose_name
