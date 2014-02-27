/*  Copyright 2013, Raphael Estrada
    Author email:  <galaktor@gmx.de>
    Project home:  <https://github.com/galaktor/gorf24>
    Licensed under The GPL v3 License (see README and LICENSE files) */
package xaddr

import (
	"testing"

	"github.com/galaktor/gorf24/reg/addr"
)
 
func TestNewPartial_LSByte_AlwaysZero(t *testing.T) {
	expected := [5]byte{0xFF, 0xFF, 0xFF, 0xFF, 0x00}

	a := NewPartial(addr.A(0), someFullXAddr(0xFFFFFFFFFF))

	actual := a.Get()
	if actual != expected {
		t.Errorf("expected '%b' but found '%b' with partaddr '%v'", expected, actual, a)
	}
}

func TestByte_ParentMSBytesZero_FirstFourBytesZero(t *testing.T) {
	expected := [5]byte{0x00, 0x00, 0x00, 0x00, 0xFF}
	root := someFullXAddr(0x0000000000)
	a := NewPartialFrom(addr.A(0), root, 0xFF)

	actual := a.Get()

	if actual != expected {
		t.Errorf("expected '%b' but found '%b' with partaddr '%v'", expected, actual, a)
	}
}

func TestByte_ParentMSBytesOnes_FirstFourBytesOnes(t *testing.T) {
	expected := [5]byte{0xFF, 0xFF, 0xFF, 0xFF, 0xAA}
	root := someFullXAddr(0xFFFFFFFFFF)
	a := NewPartialFrom(addr.A(0), root, 0xAA)

	actual := a.Get()

	if actual != expected {
		t.Errorf("expected '%b' but found '%b' with partaddr '%v'", expected, actual, a)
	}
}

func TestByte_ParentMSByteChanges_ByteMsbChangesWithParent(t *testing.T) {
	expected := [5]byte{0xFF, 0xFF, 0xFF, 0xFF, 0xA1}
	root := someFullXAddr(0x0000000000)
	a := NewPartialFrom(addr.A(0), root, 0xA1)
	
	root.Set(NewFromB5([5]byte{0xFF, 0xFF, 0xFF, 0xFF, 0xFF}))
	actual := a.Get()

	if actual != expected {
		t.Errorf("expected '%b' but found '%b' with partaddr '%v'", expected, actual, a)
	}
}

func someFullXAddr(flags uint64) *Full {
	return NewFull(addr.A(0), NewFromI(flags))
}
