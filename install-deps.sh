#!/usr/bin/env bash

sudo apt-get -qq update &&
sudo apt-get -qq install gettext xorg-dev libx11-xcb-dev libxcb-util0-dev

git clone --recursive https://github.com/boostorg/boost.git
cd boost
./bootstrap.sh
sudo ./b2 install
cd ..

