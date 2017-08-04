LIB_DIR ?= ../lib
INCLUDE_DIR ?= ../include
CFLAGS=-static -static-libstdc++ -I$(INCLUDE_DIR)
LDFLAGS=-L$(LIB_DIR) -lrf24
