#!/usr/bin/env python

# pylint: disable=invalid-name, line-too-long

import os
import shlex
import subprocess

BOOST_DIR     = 'boost_1_57_0'
BOOST_ARCHIVE = '{}.tar.gz'.format(BOOST_DIR)
BOOST_URL     = 'http://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.tar.gz'

def run_command(cmd):
	subprocess.check_output(
		shlex.split(
			cmd,
		)
	)

def install_apt():
	run_command(
		'sudo apt-get -qq update',
	)

	run_command(
		'sudo apt-get -qq install gettext xorg-dev libx11-xcb-dev libxcb-util0-dev',
	)

def install_boost():
	run_command(
		'wget -O {} {}'.format(
			BOOST_ARCHIVE,
			BOOST_URL,
		),
	)

	run_command(
		'tar xf {}'.format(
			BOOST_ARCHIVE,
		),
	)

	run_command(
		'mv {} boost'.format(
			BOOST_DIR,
		),
	)

	os.chdir('boost')
	run_command(
		'./bootstrap.sh --prefix=/usr',
	)

	run_command(
		'sudo ./b2 --prefix=/usr -q -d0 link=static thread=multi address-model=64 architecture=x86 install',
	)
	os.chdir('..')

def main():
	install_apt()
	install_boost()

if __name__ == '__main__':
	main()

