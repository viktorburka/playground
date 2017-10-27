# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models

# Create your models here.

class Urls(models.Model):
    url = models.TextField(max_length=300)
    freq = models.IntegerField(default=1)
    expStatus = models.IntegerField(default=200)
    expString = models.TextField(max_length=1000, null=True, blank=True)

class UrlChecks(models.Model):
    url = models.TextField(max_length=300)
    timeChecked = models.TextField(max_length=20)
    statusCode = models.IntegerField(default=200)
    state = models.TextField(max_length=20)