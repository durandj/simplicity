#!/usr/bin/env bash

sudo apt-get -qq update &&
sudo apt-get -qq install gettext xorg-dev libx11-xcb-dev libxcb-util0-dev

wget -O boost_1_57_0.tar.gz http://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.tar.gz
tar xf boost_1_57_0.tar.gz
mv boost_1_57_0 boost
cd boost
./bootstrap.sh --prefix=/usr
sudo ./b2 --prefix=/usr -q -d0 link=static threading=multi address-model=64 architecture=x86 install
cd ..
sudo rm -rf boost boost_1_57_0.tar.gz

