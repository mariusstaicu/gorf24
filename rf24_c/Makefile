include Makefile.inc

all:build install

build:
	$(CXX) $(CXX_FLAGS) -o librf24_c.so *.cpp

install:
	@echo "Installing cgo headers..."
	cp RF24_c.h /usr/local/include/
	@echo "Installing cgo lib..."
	cp librf24_c.so /usr/local/lib/

clean:
	rm librf24_c.so