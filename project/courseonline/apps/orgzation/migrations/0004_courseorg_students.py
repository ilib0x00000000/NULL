# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2017-07-19 15:59
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('orgzation', '0003_courseorg_lesson_total'),
    ]

    operations = [
        migrations.AddField(
            model_name='courseorg',
            name='students',
            field=models.IntegerField(default=0, verbose_name='\u5b66\u4e60\u4eba\u6570'),
        ),
    ]
