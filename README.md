# Travis CI build status
[![Build Status](https://travis-ci.org/mariusstaicu/gorf24.svg?branch=master)](https://travis-ci.org/mariusstaicu/gorf24)

# Radio-fy your Raspberry Pi
It's software that allows you to control the low-cost Nordic Semiconductor nRF24L01+ radio transceiver. It's written and tested on/for Raspberry Pi, but can be slightly modified to work for other end devices as well.

Note that this is project is in progress, and the golang or ansi C wrapper haven't been fully tested yet.
Basic send/receive testing has occured, but many functions might have bugs.
Please log any issue you might find and I will try to address it when I get a chance!
Or even better, fork and contribute, that would be much appreciated.


## Changing GPIO and SPI access
* This is just an up-to-date for the older version of the library written by galaktor ((https://travis-ci.org/galaktor/gorf24)).It is working wit the lastest RF24 Library.
It works or can be modified to make it work on any system that satisfies the following conditions:
* Linux OS
* SPI
I developed it on/for the Raspberry Pi running Arch Linux for ARM. The Pi has GPIO pins with SPI. If your device needs to control the pins and/or SPI differently, the relevant code is simple and not very hard to change. The majority of gorf24 code deals with the transceiver logic according to the official specification and will work if you can make the gpio and spi code work for you.

## HOW TO INSTALL
```
$> go get github.com/mariusstaicu/gorf24
```

## Build nRF24 Wrapper on RPi
```bash
make
```

## Cross compile nRF24 wrapper
```
 make CC=<gcc_compiler> CXX=<g++_compiler> GOOS=linux GOARCH=arm GOARM=6 (RPi Zero)
```
## Where to get gcc-linaro compilers

### from RPi tools repo: 
```
git clone -depth=1 https://github.com/raspberrypi/tools ~/rpi_tools
export PATH="$PATH:$HOME/rpi_tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin"
make CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-gcc GOOS=linux GOARCH=arm GOARM=6
```
### building your own using crosstool-ng - great tutorial here:
http://elinux.org/RPi_Linaro_GCC_Compilation

# COPYRIGHT AND LICENSE

Copyright 2013, 2014 Raphael Estrada

Licensed under the [GNU General Public License verison 3](http://www.gnu.org/licenses/gpl-3.0.txt "GNU GPL v3")

```
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```


# THE GIANTS' SHOULDERS
Kudos to Galaktor for the initial work <https://github.com/galaktor/gorf24> .Also check the native go port he has made. 

I wrote the current version of gorf24 entirely from
scratch, mostly based on the following sources:

* spidev documentation:    <https://www.kernel.org/doc/Documentation/spi/spidev>
* RPi gpio tutorial:       <https://sites.google.com/site/semilleroadt/raspberry-pi-tutorials/gpio>
* nRF24L01+ specification: <http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01P>

Early versions of gorf24 dynamically linked to the RF24
library for Raspberry Pi by Stanley Seow. Some of the
comments in the code pointed me in the right direction,
most notably with regards to timing.
<https://github.com/stanleyseow/RF24>

Seow's work is stronly derived from maniacbug's original RF24 library.
Much kudos to maniacbug for the great work.
https://github.com/maniacbug/RF24
http://maniacbug.wordpress.com/


# TODOS
* ~~Makefiles instead of shell scripts~~
* ~~maybe better way of installing via go get?~~
* more testing of correct wrapping, data types etc
* branch that includes verified-working snap of RF24-rpi
* download with RPi binaries for armv6?


