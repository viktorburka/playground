# -*- coding: utf-8 -*-
# Generated by Django 1.11.5 on 2017-09-28 02:53
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('urlchecker', '0003_auto_20170927_2249'),
    ]

    operations = [
        migrations.AlterField(
            model_name='urls',
            name='expString',
            field=models.TextField(blank=True, max_length=1000, null=True),
        ),
    ]
