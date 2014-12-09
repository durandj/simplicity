#!/usr/bin/env bash

sudo add-apt-repository -y ppa:boost-latest/ppa &&
sudo apt-get update &&
sudo apt-get install gettext xorg-dev libx11-xcb-dev libxcb-util0-dev libboost-all-dev

