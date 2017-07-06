#!/bin/sh

#  Copyright 2017, Marius Staicu,Marian Craciunescu
#  Authors email:  <marius.s.staicu@gmail.com> <marian.craciunescu@esolutions.ro>
#  Project home:  <https://github.com/mariusstaicu/gorf24>
#  Licensed under The MIT License (see README and LICENSE files)

echo "Fetching latest C++ RF24 for Raspberry Pi"
if cd RF24; then
    git pull origin master;
else
    git clone https://github.com/TMRh20/RF24 RF24;
fi

echo "Building C++ RF24 for Raspberry Pi"
cd RF24/
make
make install
cd ../

echo "Building C++ RF24 for Raspberry Pi EXAMPLES"
cd RF24/examples_linux/
make
cd ../..

echo "Building ANSI C wrapper for C++ RF24 library"
cd RF24_c
make
make install
cd ../

echo "Building goRF24 library."