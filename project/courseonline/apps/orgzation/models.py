# -*- coding:utf-8 -*-
from __future__ import unicode_literals
from datetime import datetime

from django.db import models

# Create your models here.


class City(models.Model):
    name = models.CharField(max_length=20, verbose_name='城市名')
    desc = models.TextField(verbose_name='描述')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = '城市信息'
        verbose_name_plural = verbose_name

    def __unicode__(self):
        return self.name

    __str__ = __unicode__


class CourseOrg(models.Model):
    name = models.CharField(max_length=50, verbose_name='机构名称')
    desc = models.TextField(verbose_name='机构描述')
    tag = models.CharField(max_length=30, default='全国知名', verbose_name='标签')
    classify = models.IntegerField(choices=((1, '学校'), (2, '培训班'), (3, '个人')), default=1, verbose_name='机构分类')
    click_nums = models.IntegerField(default=0, verbose_name='点击数')
    fav_nums = models.IntegerField(default=0, verbose_name='收藏数')
    students = models.IntegerField(default=0, verbose_name='学习人数')
    lesson_total = models.IntegerField(default=0, verbose_name='课程数')
    image = models.ImageField(max_length=100, upload_to='org/%Y/%m', verbose_name='封面图')
    address = models.CharField(max_length=150, verbose_name='机构地址')
    city = models.ForeignKey(City, verbose_name='机构城市')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = '机构信息'
        verbose_name_plural = verbose_name

    def get_courses(self):
        return sum([teacher.course_set.all().count() for teacher in self.teacher_set.all()])

    def get_teachers(self):
        return self.teacher_set.all().count()

    def __unicode__(self):
        return self.name

    __str__ = __unicode__


class Teacher(models.Model):
    """
    课程和教师中有一个多余的字段------所属机构
    """
    org = models.ForeignKey(CourseOrg, verbose_name='所属机构')
    name = models.CharField(max_length=50, verbose_name='教师名')
    image = models.ImageField(upload_to='teacher/%Y/%m', verbose_name='教师照片', max_length=100, blank=True, null=True)
    work_years = models.IntegerField(default=0, verbose_name='工作年限')
    work_company = models.CharField(max_length=50, verbose_name='就职公司')
    work_position = models.CharField(max_length=50, verbose_name='公司职位')
    points = models.CharField(max_length=50, verbose_name='教学特点')
    age = models.IntegerField(default=18, verbose_name='教师年龄')
    click_nums = models.IntegerField(default=0, verbose_name='点击数')
    fav_nums = models.IntegerField(default=0, verbose_name='收藏数')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = '教师信息'
        verbose_name_plural = verbose_name

    def get_course(self):
        return self.course_set.all().count()

    def __unicode__(self):
        return self.name

    __str__ = __unicode__










