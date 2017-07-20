include Makefile.inc

all:build

build: build-wrapper build-go

build-wrapper:
	@echo Building ANSI C wrapper for C++ RF24 library
	$(MAKE) -C RF24_c
	@echo Building

build-go:
	go build -v ./...