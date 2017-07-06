all:build install

RF24_LIB_ROOT=../RF24/
CC=g++
CC_FLAGS=-g -O2 -fPIC -Wall -ansi -pedantic -shared

build:
	$(CC)  $(CC_FLAGS) -I$(RF24_LIB_ROOT) -lrf24-bcm -I. -L$(RF24_LIB_ROOT)  -o librf24_c.so *.cpp

install:
	@echo "Copying cgo wrapper in /usr/lib. Sudo needed."
	cp librf24_c.so /usr/local/lib
	cp librf24_c.so /usr/lib
	@echo "Executing ldconfig."
	ldconfig

clean:
	rm -rf *.so