#!/usr/bin/env python

from __future__ import print_function

import argparse
import datetime
import dateutil.tz
import jinja2
import os
import os.path
import subprocess

# pylint: disable=invalid-name

def create_blog_post(args):
	name       = args.name
	categories = args.categories

	template = jinja2.Template(
"""---
layout:     post
title:      "{{ name }}"
date:       {{ timestamp }}
categories: {{ categories }}
---
"""
	)

	timestamp = datetime.datetime.now().replace(tzinfo = dateutil.tz.tzlocal())

	filename = '{}-{}-{}-{}.markdown'.format(
		timestamp.year,
		timestamp.month,
		timestamp.day,
		name.lower().replace(' ', '-')
	)
	path     = os.path.dirname(__file__)
	filepath = os.path.join(path, '_posts', filename)
	with open(filepath, 'w') as fh:
		fh.write(
			template.render(
				categories = ' '.join(categories),
				name       = name,
				timestamp  = timestamp.replace(microsecond = 0).isoformat(),
			)
		)

	editor = os.environ.get('EDITOR', 'vim')
	subprocess.call([editor, filepath])

def run_server(args):
	subprocess.call(
		[
			'bundle',
			'exec',
			'jekyll',
			'serve',
		]
	)

def parse_args():
	parser = argparse.ArgumentParser(description = 'Management tool for the blog')

	subparsers = parser.add_subparsers(help = 'Command')

	create_post_parser = subparsers.add_parser(
		'post',
		help = 'Create a new blog post',
	)
	create_post_parser.add_argument(
		'name',
		type = str,
		help = 'The blog post name',
	)
	create_post_parser.add_argument(
		'categories',
		type    = str,
		nargs   = '*',
		default = ['update'],
		help    = 'Blog post categories',
	)
	create_post_parser.set_defaults(func = create_blog_post)

	run_server_parser = subparsers.add_parser(
		'server',
		help = 'Run a development server',
	)
	run_server_parser.set_defaults(func = run_server)

	return parser.parse_args()

def main():
	args = parse_args()

	args.func(args)

if __name__ == '__main__':
	main()

