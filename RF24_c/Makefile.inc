LIB_DIR ?= ../lib
INCLUDE_DIR ?= ../include
CFLAGS=-shared -I$(INCLUDE_DIR)
LDFLAGS=-L$(LIB_DIR) -lrf24
