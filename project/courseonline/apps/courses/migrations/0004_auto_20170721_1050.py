# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2017-07-21 10:50
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('courses', '0003_auto_20170720_1432'),
    ]

    operations = [
        migrations.CreateModel(
            name='CourseClass',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=30, verbose_name='\u8bfe\u7a0b\u7c7b\u522b\u540d')),
            ],
        ),
        migrations.AddField(
            model_name='course',
            name='classify',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='courses.CourseClass', verbose_name='\u8bfe\u7a0b\u7c7b\u522b'),
        ),
    ]