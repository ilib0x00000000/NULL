# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2017-07-19 15:23
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('orgzation', '0002_courseorg_classify'),
    ]

    operations = [
        migrations.AddField(
            model_name='courseorg',
            name='lesson_total',
            field=models.IntegerField(default=0, verbose_name='\u8bfe\u7a0b\u6570'),
        ),
    ]
