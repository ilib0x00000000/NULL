# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2017-07-20 10:37
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('orgzation', '0004_courseorg_students'),
        ('courses', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='course',
            name='orgname',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='orgzation.CourseOrg', verbose_name='\u6240\u5c5e\u673a\u6784'),
        ),
    ]
