#!/bin/bash
apt-get update
apt-get install -y cmake
apt-get install -y make
apt-get install -y build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev
cd /usr/src/app/src/build
cmake ..
make
cp /usr/src/app/src/build/api-server /usr/src/app/bin/api-server
