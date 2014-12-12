#!/usr/bin/env bash

sudo apt-get -qq update &&
sudo apt-get -qq install gettext xorg-dev libx11-xcb-dev libxcb-util0-dev

git clone --recursive --quiet https://github.com/boostorg/boost.git
cd boost
./bootstrap.sh --prefix=/usr
sudo ./b2 --prefix=/usr link=shared threading=multi address-model=64 architecture=x86
cd ..
rm -rf boost

