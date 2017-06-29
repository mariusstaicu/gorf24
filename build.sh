#!/bin/bash

#  Copyright 2017, Marius Staicu
#  Author email:  <marius.s.staicu@gmail.com>
#  Project home:  <https://github.com/mariusstaicu/gorf24>
#  Licensed under The MIT License (see README and LICENSE files)

echo "fetching C++ RF24 for Raspberry Pi"
git clone https://github.com/TMRh20/RF24

echo "building C++ RF24 for Raspberry Pi"
cd RF24/
make
make install
cd ../

echo "building C++ RF24 for Raspberry Pi EXAMPLES"
cd RF24/examples_linux/
make
cd ../..

echo "buliding ANSI C wrapper for C++ RF24 library"
cd RF24_c
bash build.sh
cd ..



