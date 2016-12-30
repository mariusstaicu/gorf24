#!/bin/bash

#  Copyright 2013, Raphael Estrada
#  Author email:  <galaktor@gmx.de>
#  Project home:  <https://github.com/galaktor/gorf24>
#  Licensed under The MIT License (see README and LICENSE files)

rfhdrdir=../RF24/RPi/RF24/
rflibdir=$rfhdrdir

g++ -g -O2 -fPIC -I$rfhdrdir -lrf24-bcm -I. -L$rflibdir  -shared -o librf24_c.so *.cpp -ansi -pedantic

cp librf24_c.so /usr/local/lib

# pick up new shared objects
# will only work if /usr/local/lib is in /etc/ld.so.conf!
# see README for details
ldconfig

