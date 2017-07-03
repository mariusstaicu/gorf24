/*  Copyright 2013, Raphael Estrada
    Author email:  <galaktor@gmx.de>
    Project home:  <https://github.com/galaktor/gorf24>
    Licensed under The MIT License (see README and LICENSE files)

    Updated to RF24 v.13
    2017, Marian Craciunescu, Marius Staicu
    Authors email:  <marian.craciunescu@esolutions.ro>, <marius.staicu@esolutions.ro>
    Project home:  <https://github.com/mariusstaicu/gorf24>
*/
package gorf24

/*
  #cgo LDFLAGS: -L./RF24_c
  #cgo LDFLAGS: -lrf24_c
  #cgo CFLAGS: -I./RF24_c
  #include "RF24_c.h"
  #include <stdio.h>
*/
import "C"
import (
	// "encoding/binary"
	// "fmt"
	"unsafe"
)

type LibRF24 interface {
	Begin()
	Delete()
	StartListening()
	StopListening()
	Write(data []byte, length uint8) bool
	StartWrite(data []byte, length uint8)
	WriteAckPayload(pipe uint8, data []byte, length uint8)
	Available() bool
	AvailablePipe() (bool, uint8)
	IsAckPayloadAvailable() bool
	Read(length uint8) ([]byte, bool)
	OpenWritingPipe(address uint64)
	OpenReadingPipe(pipe uint8, address uint64)
	SetRetries(delay uint8, count uint8)
	SetChannel(channel uint8)
	SetPayloadSize(size uint8)
	GetPayloadSize() uint8
	GetDynamicPayloadSize() uint8
	EnableAckPayload()
	EnableDynamicPayloads()
	IsPVariant() bool
	SetAutoAck(enable bool)
	SetAutoAckPipe(pipe uint8, enable bool)
	SetPALevel(level PA_DBM)
	GetPALevel() PA_DBM
	SetDataRate(rate DATARATE)
	GetDataRate() DATARATE
	SetCRCLength(length CRCLENGTH)
	GetCRCLength() CRCLENGTH
	DisableCRC()
	PrintDetails()
	PowerDown()
	PowerUp()
	WhatHappened() (tx_ok, tx_fail, rx_ready bool)
	TestCarrier() bool
	TestRPD() bool
}

// TODO: more idiomatic:
//   error handling
//   Read/Write interfaces
//   possibly more conventional byte slice passing
//   more type safety?
//   channel for available data, like time.Tick? r.Available() <-chan []byte  or so?
type RF24 struct {
	cptr        C.RF24Handle
	buffer_size uint8
	buffer      []byte
}

/*
func main() {
	var pipe uint64 = 0xF0F0F0F0E1
	r := New(25, 8, 32)
	defer r.Delete()
	r.Begin()
	r.SetRetries(15, 15)
	r.SetAutoAck(true)
	r.OpenReadingPipe(1, pipe)
	r.StartListening()
	r.PrintDetails()
	for {
		if r.Available() {
			data, _ := r.Read(4)
//			fmt.Printf("data: %v\n", data)
			payload := binary.LittleEndian.Uint32(data)
			fmt.Printf("Received %v\n", payload)
		} else {
			//
		}
	}
}
*/
func New(cepin uint8, cspin uint8, spispeed uint32) LibRF24 {
	var r RF24
	r.cptr = C.new_rf24(C.uint8_t(cepin), C.uint8_t(cspin), C.uint32_t(spispeed))
	r.buffer = make([]byte, 128) // max payload length according to nrf24 spec
	return &r
}

func (r *RF24) Delete() {
	C.rf24_delete(r.cptr)
	r.cptr = nil
}
func (r *RF24) Begin() {
	C.rf24_begin(r.cptr)
}

func (r *RF24) StartListening() {
	C.rf24_startListening(r.cptr)
}

func (r *RF24) StopListening() {
	C.rf24_stopListening(r.cptr)
}

// TODO: implement Reader/Writer compatible interfaces
func (r *RF24) Write(data []byte, length uint8) bool {
	return gobool(C.rf24_write(r.cptr, unsafe.Pointer(&data[0]), C.uint8_t(length)))
}
func (r *RF24) StartWrite(data []byte, length uint8) {
	C.rf24_startWrite(r.cptr, unsafe.Pointer(&data), C.uint8_t(length))
}
func (r *RF24) WriteAckPayload(pipe uint8, data []byte, length uint8) {
	C.rf24_writeAckPayload(r.cptr, C.uint8_t(pipe), unsafe.Pointer(&data), C.uint8_t(length))
}
func (r *RF24) Available() bool {
	return gobool(C.rf24_available(r.cptr))
}

// TODO: create Pipe type, make this a func on Pipe
func (r *RF24) AvailablePipe() (bool, uint8) {
	var pipe C.uint8_t
	available := gobool(C.rf24_available_pipe(r.cptr, &pipe))
	return available, uint8(pipe)
}
func (r *RF24) IsAckPayloadAvailable() bool {
	return gobool(C.rf24_isAckPayloadAvailable(r.cptr))
}
func (r *RF24) Read(length uint8) ([]byte, bool) {
	ok := gobool(C.rf24_read(r.cptr, unsafe.Pointer(&r.buffer[0]), C.uint8_t(length)))
	return r.buffer[:length], ok
}
func (r *RF24) OpenWritingPipe(address uint64) {
	C.rf24_openWritingPipe(r.cptr, C.uint64_t(address))
}
func (r *RF24) OpenReadingPipe(pipe uint8, address uint64) {
	C.rf24_openReadingPipe(r.cptr, C.uint8_t(pipe), C.uint64_t(address))
}
func (r *RF24) SetRetries(delay uint8, count uint8) {
	C.rf24_setRetries(r.cptr, C.uint8_t(delay), C.uint8_t(count))
}
func (r *RF24) SetChannel(channel uint8) {
	C.rf24_setChannel(r.cptr, C.uint8_t(channel))
}
func (r *RF24) SetPayloadSize(size uint8) {
	C.rf24_setPayloadSize(r.cptr, C.uint8_t(size))
}
func (r *RF24) GetPayloadSize() uint8 {
	return uint8(C.rf24_getPayloadSize(r.cptr))
}
func (r *RF24) GetDynamicPayloadSize() uint8 {
	return uint8(C.rf24_getDynamicPayloadSize(r.cptr))
}
func (r *RF24) EnableAckPayload() {
	C.rf24_enableAckPayload(r.cptr)
}
func (r *RF24) EnableDynamicPayloads() {
	C.rf24_enableDynamicPayloads(r.cptr)
}
func (r *RF24) IsPVariant() bool {
	return gobool(C.rf24_isPVariant(r.cptr))
}
func (r *RF24) SetAutoAck(enable bool) {
	C.rf24_setAutoAck(r.cptr, cbool(enable))
}
func (r *RF24) SetAutoAckPipe(pipe uint8, enable bool) {
	C.rf24_setAutoAck_pipe(r.cptr, C.uint8_t(pipe), cbool(enable))
}

// Is there any way to use the rf24_pa_dbm_e enum type directly
func (r *RF24) SetPALevel(level PA_DBM) {
	C.rf24_setPALevel(r.cptr, C.rf24_pa_dbm_val(level))
}
func (r *RF24) GetPALevel() PA_DBM {
	return PA_DBM(C.rf24_getPALevel(r.cptr))
}

func (r *RF24) SetDataRate(rate DATARATE) {
	C.rf24_setDataRate(r.cptr, C.rf24_datarate_val(rate))
}
func (r *RF24) GetDataRate() DATARATE {
	return DATARATE(C.rf24_getDataRate(r.cptr))
}

func (r *RF24) SetCRCLength(length CRCLENGTH) {
	C.rf24_setCRCLength(r.cptr, C.rf24_crclength_val(length))
}
func (r *RF24) GetCRCLength() CRCLENGTH {
	return CRCLENGTH(C.rf24_getCRCLength(r.cptr))
}
func (r *RF24) DisableCRC() {
	C.rf24_disableCRC(r.cptr)
}

// TODO: String() method would be great
func (r *RF24) PrintDetails() {
	C.rf24_printDetails(r.cptr)
}
func (r *RF24) PowerDown() {
	C.rf24_powerDown(r.cptr)
}
func (r *RF24) PowerUp() {
	C.rf24_powerUp(r.cptr)
}
func (r *RF24) WhatHappened() (tx_ok, tx_fail, rx_ready bool) {
	var out_tx_ok, out_tx_fail, out_rx_ready C.cbool
	C.rf24_whatHappened(r.cptr, &out_tx_ok, &out_tx_fail, &out_rx_ready)
	tx_ok, tx_fail, rx_ready = gobool(out_tx_ok), gobool(out_tx_fail), gobool(out_rx_ready)
	return
}

func (r *RF24) TestCarrier() bool {
	return gobool(C.rf24_testCarrier(r.cptr))
}
func (r *RF24) TestRPD() bool {
	return gobool(C.rf24_testRPD(r.cptr))
}

// TODO: @Marian Craciunescu add missing function implementation.
