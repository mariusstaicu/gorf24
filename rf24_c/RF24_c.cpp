/*  Copyright 2013, Raphael Estrada
    Author email:  <galaktor@gmx.de>
    Project home:  <https://github.com/galaktor/gorf24>
    Licensed under The MIT License (see README and LICENSE files)

    Updated to RF24 v.13
    2017, Marian Craciunescu, Marius Staicu
    Authors email:  <marian.craciunescu@esolutions.ro>, <marius.staicu@esolutions.ro>
    Project home:  <https://github.com/mariusstaicu/gorf24>
    */
#include <RF24/RF24.h>
#include "RF24_c.h"
#include <string>

#define to_rfh(ptr) (reinterpret_cast<RF24Handle>(ptr))
#define to_rf(ptr)  (reinterpret_cast<RF24*>(ptr))
#define dbm_to_e(val) (static_cast<rf24_pa_dbm_e>(val))
#define crc_to_e(val) (static_cast<rf24_crclength_e>(val))
#define dat_to_e(val) (static_cast<rf24_datarate_e>(val))

RF24Handle new_rf24(uint8_t ce, uint8_t cs, uint32_t spispeed) {
    RF24 *r = new RF24(ce, cs, spispeed);
    return to_rfh(r);
}

RF24Handle new_rf24_optional(uint8_t ce, uint8_t cs) {
    RF24 *r = new RF24(ce, cs);
    return to_rfh(r);
}

void rf24_delete(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    delete r;
}

void rf24_begin(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->begin();
}

cbool rf24_isChipConnected(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->isChipConnected());
}

void rf24_startListening(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->startListening();
}

void rf24_stopListening(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->stopListening();
}

cbool rf24_available(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->available());
}

cbool rf24_read(RF24Handle rf_handle, void *target, uint8_t len) {
    RF24 *r = to_rf(rf_handle);
    if (r->available()) {
        r->read(target, len);
        return TRUE;
    }
    return FALSE;
}

cbool rf24_write(RF24Handle rf_handle, const void *source, uint8_t len) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->write(source, len));
}


void rf24_openWritingPipe(RF24Handle rf_handle, uint64_t address) {
    RF24 *r = to_rf(rf_handle);
    r->openWritingPipe(address);
}

void rf24_openReadingPipe(RF24Handle rf_handle, uint8_t pipe,
                          uint64_t address) {
    RF24 *r = to_rf(rf_handle);
    r->openReadingPipe(pipe, address);
}

void rf24_printDetails(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->printDetails();
}

cbool rf24_available_pipe(RF24Handle rf_handle, uint8_t *out_pipe) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->available(out_pipe));
}

cbool rf24_rxFifoFull(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->rxFifoFull());
}

void rf24_powerDown(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->powerDown();
}

void rf24_powerUp(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->powerUp();
}

cbool rf24_writeMulticast(RF24Handle rf_handle, const void *buf, uint8_t len, const cbool multicast) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->write(buf, len, multicast));
}

cbool rf24_writeFast(RF24Handle rf_handle, const void *buf, uint8_t len) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->writeFast(buf, len));
}

cbool rf24_writeFastMulticast(RF24Handle rf_handle, const void *buf, uint8_t len, const cbool multicast) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->writeFast(buf, len, multicast));
}

cbool rf24_writeBlocking(RF24Handle rf_handle, const void *buf, uint8_t len, uint32_t timeout) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->writeBlocking(buf, len, timeout));
}

cbool rf24_txStandBy(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->txStandBy());
}

cbool rf24_txStandByExtended(RF24Handle rf_handle, uint32_t timeout, cbool startTx) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->txStandBy(timeout, startTx));
}

void rf24_writeAckPayload(RF24Handle rf_handle, uint8_t pipe,
                          const void *source, uint8_t len) {
    RF24 *r = to_rf(rf_handle);
    r->writeAckPayload(pipe, source, len);
}

cbool rf24_isAckPayloadAvailable(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->isAckPayloadAvailable());
}

void rf24_whatHappened(RF24Handle rf_handle, cbool *out_tx_ok, cbool *out_tx_fail, cbool *out_rx_ready) {
    bool tx_ok, tx_fail, rx_ready;
    RF24 *r = to_rf(rf_handle);
    r->whatHappened(tx_ok, tx_fail, rx_ready);
    *out_tx_ok = cbool(tx_ok);
    *out_tx_fail = cbool(tx_fail);
    *out_rx_ready = cbool(rx_ready);
}

void rf24_startWrite(RF24Handle rf_handle, const void *source, uint8_t len, const cbool multicast) {
    RF24 *r = to_rf(rf_handle);
    r->startWrite(source, len, multicast);
}

void rf24_startFastWrite(RF24Handle rf_handle, const void *buf, uint8_t len, const cbool multicast, cbool startTx) {
    RF24 *r = to_rf(rf_handle);
    r->startFastWrite(buf, len, multicast, TRUE);
}

void rf24_reUseTX(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->reUseTX();
}

uint8_t rf24_flush_tx(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return r->flush_tx();
}

cbool rf24_testCarrier(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return (cbool(r->testCarrier()));
}

cbool rf24_testRPD(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->testRPD());
}

void rf24_closeReadingPipe(RF24Handle rf_handle, uint8_t pipe) {
    RF24 *r = to_rf(rf_handle);
    r->closeReadingPipe(pipe);
}

void rf24_setAddressWidth(RF24Handle rf_handle, uint8_t a_width) {
    RF24 *r = to_rf(rf_handle);
    r->setAddressWidth(a_width);
}

void rf24_setRetries(RF24Handle rf_handle, uint8_t delay, uint8_t count) {
    RF24 *r = to_rf(rf_handle);
    r->setRetries(delay, count);
}

void rf24_setChannel(RF24Handle rf_handle, uint8_t channel) {
    RF24 *r = to_rf(rf_handle);
    r->setChannel(channel);
}

uint8_t rf24_getChannel(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return r->getChannel();
}

void rf24_setPayloadSize(RF24Handle rf_handle, uint8_t size) {
    RF24 *r = to_rf(rf_handle);
    r->setPayloadSize(size);
}

uint8_t rf24_getPayloadSize(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return r->getPayloadSize();
}

uint8_t rf24_getDynamicPayloadSize(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return r->getDynamicPayloadSize();
}

void rf24_enableAckPayload(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->enableAckPayload();
}

void rf24_enableDynamicPayloads(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->enableDynamicPayloads();
}

void rf24_disableDynamicPayloads(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->disableDynamicPayloads();
}

void rf24_enableDynamicAck(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->enableDynamicAck();
}

cbool rf24_isPVariant(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->isPVariant());
}

void rf24_setAutoAck(RF24Handle rf_handle, cbool enable) {
    RF24 *r = to_rf(rf_handle);
    r->setAutoAck(enable);
}

void rf24_setAutoAck_pipe(RF24Handle rf_handle, uint8_t pipe, cbool enable) {
    RF24 *r = to_rf(rf_handle);
    r->setAutoAck(pipe, enable);
}

void rf24_setPALevel(RF24Handle rf_handle, rf24_pa_dbm_val level) {
    RF24 *r = to_rf(rf_handle);
    r->setPALevel(dbm_to_e(level));
}

rf24_pa_dbm_val rf24_getPALevel(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return r->getPALevel();
}

cbool rf24_setDataRate(RF24Handle rf_handle, rf24_datarate_val speed) {
    RF24 *r = to_rf(rf_handle);
    return cbool(r->setDataRate(dat_to_e(speed)));
}

rf24_datarate_val rf24_getDataRate(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return r->getDataRate();
}

void rf24_setCRCLength(RF24Handle rf_handle, rf24_crclength_val length) {
    RF24 *r = to_rf(rf_handle);
    r->setCRCLength(crc_to_e(length));
}

rf24_crclength_val rf24_getCRCLength(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    return r->getCRCLength();
}

void rf24_disableCRC(RF24Handle rf_handle) {
    RF24 *r = to_rf(rf_handle);
    r->disableCRC();
}

void rf24_maskIRQ(RF24Handle rf_handle, cbool tx_ok, cbool tx_fail, cbool rx_ready) {
    RF24 *r = to_rf(rf_handle);
    r->maskIRQ(tx_ok, tx_fail, rx_ready);
}