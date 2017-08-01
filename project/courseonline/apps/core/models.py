# -*- coding:utf-8 -*-

from __future__ import unicode_literals

from django.db import models
from django.db.models.signals import post_delete, pre_save
from django.core.cache import cache

# Create your models here.

ADMIN_ACCESS_WHITELIST_PREFIX = 'DJANGO_ADMIN_ACCESS_WHITELIST:'
WHITELIST_PREFIX = 'DJANGO_ADMIN_ACCESS_WHITELIST:'


class DjangoAdminAccessIPWhitelist(models.Model):
    whitelist_reason = models.CharField(max_length=255, help_text='Reason for the whitelist?', verbose_name='管理员白名单')
    ip = models.CharField(max_length=255, help_text='输入一个IP到管理员白名单', verbose_name='IP')

    def __unicode__(self):
        return '添加IP : %s 到管理员白名单' % self.ip

    __str__ = __unicode__

    class Meta:
        verbose_name = '允许登录后台的IP'
        verbose_name_plural = verbose_name


def _generate_cache_key(instance):
    return ADMIN_ACCESS_WHITELIST_PREFIX + instance.ip


def _update_cache(sender, **kwargs):
    new_instance = kwargs.get('instance')

    if new_instance.pk:
        old_instance = DjangoAdminAccessIPWhitelist.objects.get(pk=new_instance.pk)

        if _generate_cache_key(old_instance) != _generate_cache_key(new_instance):
            old_cache_key = _generate_cache_key(old_instance)
            cache.delete(old_cache_key)

    cache_key = _generate_cache_key(new_instance)
    cache.set(cache_key, '1')


    def _delete_cache(sender, **kwargs):
        instance = kwargs.get('instance')
        cache_key = _generate_cache_key(instance)
        cache.delete(cache_key)

    pre_save.connect(_update_cache, sender=DjangoAdminAccessIPWhitelist)
    post_delete.connect(_delete_cache, sender=DjangoAdminAccessIPWhitelist)