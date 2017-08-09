include Makefile.inc
SHELL = /bin/bash

all:build

build: build-rf24 build-wrapper

build-rf24: clone-rf24
	@echo Building RF24 shared libraries
	cd rf24; \
	git checkout v1.3.0; \
	./configure --driver=RPi --c_compiler=$(CC) --cxx_compiler=$(CXX); \
	make && make install; \

clone-rf24:
	@if [ ! -d "rf24" ]; then \
		echo "Cloning $(rf24.repo) into rf24..."; \
		git clone $(rf24.repo) rf24;\
	fi

build-wrapper:
	@echo Building ANSI C wrapper for C++ RF24 library
	cd rf24_c && $(MAKE); \

clean:
	$(MAKE) clean -C rf24_c; \
	$(MAKE) clean -C rf24; \
	rm -r rf24;