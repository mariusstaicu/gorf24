package gorf24

/*
  #cgo LDFLAGS: -L./RF24_c
  #cgo LDFLAGS: -lrf24_c
  #cgo CFLAGS: -I./RF24_c
  #include "RF24_c.h"
  #include <stdio.h>
*/
import "C"

func gobool(b C.cbool) bool {
	if b == C.cbool(0) {
		return false
	}
	return true
}

func cbool(b bool) C.cbool {
	if b {
		return C.cbool(1)
	}
	return C.cbool(0)
}
