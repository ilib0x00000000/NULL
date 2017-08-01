# -*- coding:utf-8 -*-

from __future__ import unicode_literals
from datetime import datetime

from django.db import models

from orgzation.models import CourseOrg
from orgzation.models import Teacher

# Create your models here.


class CourseClass(models.Model):
    """
    课程类别
    """
    name = models.CharField(max_length=30, verbose_name='课程类别名')

    class Meta:
        verbose_name = '课程分类'
        verbose_name_plural = verbose_name

    def __unicode__(self):
        return self.name

    __str__ = __unicode__


class Course(models.Model):
    teacher = models.ForeignKey(Teacher, verbose_name='课程讲师', null=True, blank=True)
    classify = models.ForeignKey(CourseClass, verbose_name='课程类别', null=True, blank=True)
    name = models.CharField(max_length=50, verbose_name='课程名')
    desc = models.CharField(max_length=300, verbose_name='课程描述')
    tags = models.CharField(max_length=100, default='', verbose_name='课程标签')
    detail = models.TextField(verbose_name='课程详情')
    is_advan = models.BooleanField(default=False, verbose_name='是否是广告')
    degree = models.CharField(max_length=2, choices=(('dj', '低级'), ('zj', '中级'), ('gj', '高级')), verbose_name='课程难度')
    learn_times = models.IntegerField(default=0, verbose_name='课程时长')
    students = models.IntegerField(default=0, verbose_name='学习人数')
    fav_nums = models.IntegerField(default=0, verbose_name='收藏人数')
    image = models.ImageField(upload_to='courses/%Y/%m', verbose_name='封面图片')
    click_nums = models.IntegerField(default=0, verbose_name='点击数')
    known_before = models.CharField(max_length=150, default='', verbose_name='课程须知')
    learn_content = models.TextField(default='', verbose_name='学习到的知识')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = '课程'
        verbose_name_plural = verbose_name

    def get_chapters(self):
        return self.lesson_set.all().count()

    def get_learner(self):
        return self.usercourse_set.all()[:5]

    def get_chapter_list(self):
        return self.lesson_set.all()

    def get_download(self):
        return self.courseresource_set.all()

    def __unicode__(self):
        return self.name

    __str__ = __unicode__


class Lesson(models.Model):
    course = models.ForeignKey(Course, verbose_name='课程')
    name = models.CharField(max_length=100, verbose_name='章节名')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = '章节'
        verbose_name_plural = verbose_name

    def __unicode__(self):
        return self.course.name + '--' + self.name

    __str__ = __unicode__

    def get_video(self):
        return self.video_set.all()


class Video(models.Model):
    lesson = models.ForeignKey(Lesson, verbose_name='章节')
    name = models.CharField(max_length=100, verbose_name='视频名')
    path = models.CharField(max_length=100, default='http://othhhjzhr.bkt.clouddn.com/courseonline-test-video-chapter.avi', verbose_name='视频路径')
    # path = models.FileField(max_length=100, upload_to='video/%Y/%m', verbose_name='视频所在路径', default='')
    minutes = models.IntegerField(default=0, verbose_name='时长-分钟')
    seconds = models.IntegerField(default=0, verbose_name='时长-秒钟')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = '视频'
        verbose_name_plural = verbose_name

    def __unicode__(self):
        return self.lesson.course.name + '--' + self.lesson.name + '--' + self.name

    __str__ = __unicode__


class CourseResource(models.Model):
    course = models.ForeignKey(Course, verbose_name='课程')
    name = models.CharField(max_length=100, verbose_name='文件名')
    download = models.FileField(upload_to='resource/%Y/%m', verbose_name='资源路径', max_length=100)
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = '课程资源'
        verbose_name_plural = verbose_name

    def __unicode__(self):
        return self.name

    __str__ = __unicode__
