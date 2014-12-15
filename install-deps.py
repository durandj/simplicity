#!/usr/bin/env python

# pylint: disable=invalid-name, line-too-long

from __future__ import print_function

import os
import re
import shlex
import shutil
import subprocess
import sys

BOOST_DIR     = 'boost_1_57_0'
BOOST_ARCHIVE = '{}.tar.gz'.format(BOOST_DIR)
BOOST_URL     = 'http://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.tar.gz'

REGEX_FLAGS = re.MULTILINE

def better_print(message, *args, **kwargs):
	print(
		message.format(
			*args,
			**kwargs
		)
	)

def run_command(cmd, regex = None):
	try:
		process = subprocess.Popen(
			shlex.split(
				cmd,
			),
			stderr = subprocess.PIPE,
			stdout = subprocess.PIPE,
		)

		if regex:
			while not process.poll():
				line = process.stdout.readline()

				if regex.findall():
					better_print(
						line,
					)

		stdout, stderr = process.communicate()
	except KeyboardInterrupt:
		better_print(
			'Command interrupted by user',
		)

		sys.exit(1)

	if process.returncode != 0:
		better_print(
			'Command failed:\n\tCommand: {}\n\tStdout:\n\t\t{}\n\tStderr:\n\t\t{}',
			cmd,
			stdout.replace('\n', '\n\t\t').rstrip(),
			stderr.replace('\n', '\n\t\t').rstrip(),
		)

		sys.exit(1)

def install_apt():
	better_print('Installing packages from Apt...')

	better_print('\tUpdating Apt cache...')
	run_command(
		'sudo apt-get -qq update',
	)

	better_print('\tInstalling packages...')
	run_command(
		'sudo apt-get -qq install gettext xorg-dev libx11-xcb-dev libxcb-util0-dev',
	)

	better_print('Finished installing Apt packages')

def install_boost():
	better_print('Installing Boost...')

	better_print('\tDownloading Boost...')
	run_command(
		'wget -O {} {}'.format(
			BOOST_ARCHIVE,
			BOOST_URL,
		),
	)

	better_print('\tUnpacking Boost...')
	run_command(
		'tar xf {}'.format(
			BOOST_ARCHIVE,
		),
	)

	if os.path.exists('boost'):
		better_print('\tRemoving old Boost directory...')
		shutil.rmtree('boost')

	os.rename(BOOST_DIR, 'boost')

	os.chdir('boost')
	better_print('\tPreparing to build Boost...')
	run_command(
		'./bootstrap.sh --prefix=/usr',
	)

	better_print('\tBuilding Boost...')
	run_command(
		'sudo ./b2 --prefix=/usr -q link=static threading=multi address-model=64 architecture=x86 install',
		re.compile(
			r'^...on \d+th target...$',
			REGEX_FLAGS,
		),
	)
	os.chdir('..')

	better_print('Finished installing Boost')

def main():
	install_apt()
	install_boost()

if __name__ == '__main__':
	main()

