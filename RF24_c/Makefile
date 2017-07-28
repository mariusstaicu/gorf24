include Makefile.inc

all:build install

build:
	$(CXX) $(CFLAGS) -o librf24_c.so *.cpp

install:
	@echo "Installing cgo headers..."
	cp RF24_c.h $(INCLUDE_DIR)
	@echo "Installing cgo lib..."
	cp librf24_c.so $(LIB_DIR)

clean:
	rm librf24_c.so
	rm $(LIB_DIR)/librf24_c.so
	rm $(Include_DIR)/RF24_c.h