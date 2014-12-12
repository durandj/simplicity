#!/usr/bin/env bash

sudo apt-get -qq update &&
sudo apt-get -qq install gettext xorg-dev libx11-xcb-dev libxcb-util0-dev

wget -O boost_1_57_0.tar.gz http://sourceforge.net/projects/boost/files/boost/1.57.0/boost_1_57_0.tar.gz/download
tar xf boost_1_57_0.tar.gz
mv boost_1_57_0 boost
cd boost
./bootstrap.sh --prefix=/usr
sudo ./b2 --prefix=/usr link=shared threading=multi address-model=64 architecture=x86
cd ..
sudo rm -rf boost boost_1_57_0.tar.gz

