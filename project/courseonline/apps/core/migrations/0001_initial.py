# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2017-07-27 08:36
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='DjangoAdminAccessIPWhitelist',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('whitelist_reason', models.CharField(help_text='Reason for the whitelist?', max_length=255, verbose_name='\u7ba1\u7406\u5458\u767d\u540d\u5355')),
                ('ip', models.CharField(help_text='\u8f93\u5165\u4e00\u4e2aIP\u5230\u7ba1\u7406\u5458\u767d\u540d\u5355', max_length=255, verbose_name='IP')),
            ],
            options={
                'verbose_name': '\u5141\u8bb8\u767b\u5f55\u540e\u53f0\u7684IP',
                'verbose_name_plural': '\u5141\u8bb8\u767b\u5f55\u540e\u53f0\u7684IP',
            },
        ),
    ]
