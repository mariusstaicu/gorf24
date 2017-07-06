/*  Copyright 2013, Raphael Estrada
    Author email:  <galaktor@gmx.de>
    Project home:  <https://github.com/galaktor/gorf24>
    Licensed under The MIT License (see README and LICENSE files)

    Updated to RF24 v.13
    2017, Marian Craciunescu, Marius Staicu
    Authors email:  <marian.craciunescu@esolutions.ro>, <marius.staicu@esolutions.ro>
    Project home:  <https://github.com/mariusstaicu/gorf24>
    */
#pragma once

#include <stdint.h>

typedef void *RF24Handle;
typedef const char *cstring;
// poor man's boolean
typedef enum {
    FALSE = 0, TRUE
} cbool;
#define cbool(X) ((X) ? TRUE : FALSE)
// cannot re-use enums because they are delcared in c++
// cannot re-declare them, either, won't compile
// so just use numbers and add type safety in higher layer wrapper
typedef uint8_t rf24_pa_dbm_val;
typedef uint8_t rf24_datarate_val;
typedef uint8_t rf24_crclength_val;
#ifdef __cplusplus
#define DLL extern "C"
#else
#define DLL
#endif

DLL RF24Handle new_rf24(uint8_t ce, uint8_t cs, uint32_t spispeed);

DLL RF24Handle new_rf24_optional(uint8_t ce, uint8_t cs);

DLL void rf24_delete(RF24Handle rf_handle);

DLL void rf24_begin(RF24Handle rf_handle);

DLL cbool rf24_isChipConnected(RF24Handle rf_handle);

DLL void rf24_startListening(RF24Handle rf_handle);

DLL void rf24_stopListening(RF24Handle rf_handle);

DLL cbool rf24_available(RF24Handle rf_handle);

DLL cbool rf24_read(RF24Handle rf_handle, void *target, uint8_t len);

DLL cbool rf24_write(RF24Handle rf_handle, const void *source, uint8_t len);

DLL void rf24_openWritingPipe(RF24Handle rf_handle, uint64_t address);

DLL void rf24_openReadingPipe(RF24Handle rf_handle, uint8_t pipe, uint64_t address);

DLL void rf24_printDetails(RF24Handle rf_handle);
// correspond to bool available(uint8_t* pipe_num);
DLL cbool rf24_available_pipe(RF24Handle rf_handle, uint8_t *out_pipe);

DLL cbool rf24_rxFifoFull(RF24Handle rf_handle);

DLL void rf24_powerDown(RF24Handle rf_handle);

DLL void rf24_powerUp(RF24Handle rf_handle);

DLL cbool rf24_writeMulticast(RF24Handle rf_handle, const void *buf, uint8_t len, const cbool multicast);

DLL cbool rf24_writeFast(RF24Handle rf_handle, const void *buf, uint8_t len);

DLL cbool rf24_writeFastMulticast(RF24Handle rf_handle, const void *buf, uint8_t len, const cbool multicast);

DLL cbool rf24_writeBlocking(RF24Handle rf_handle, const void *buf, uint8_t len, uint32_t timeout);

DLL cbool rf24_txStandBy(RF24Handle rf_handle);

DLL cbool rf24_txStandByExtended(RF24Handle rf_handle, uint32_t timeout, cbool startTx);

DLL void rf24_writeAckPayload(RF24Handle, uint8_t pipe, const void *source, uint8_t len);

DLL cbool rf24_isAckPayloadAvailable(RF24Handle rf_handle);

DLL void rf24_whatHappened(RF24Handle rf_handle, cbool *tx_ok, cbool *tx_fail, cbool *rx_ready);

DLL void rf24_startWrite(RF24Handle rf_handle, const void *source, uint8_t len, const cbool multicast);

DLL void rf24_startFastWrite(RF24Handle rf_handle, const void *buf, uint8_t len, const cbool multicast, cbool startTx);

DLL void rf24_reUseTX(RF24Handle rf_handle);

DLL uint8_t rf24_flush_tx(RF24Handle rf_handle);

DLL cbool rf24_testCarrier(RF24Handle rf_handle);

DLL cbool rf24_testRPD(RF24Handle rf_handle);

DLL void rf24_closeReadingPipe(RF24Handle rf_handle, uint8_t pipe);

DLL void rf24_setAddressWidth(RF24Handle rf_handle, uint8_t a_width);

DLL void rf24_setRetries(RF24Handle rf_handle, uint8_t delay, uint8_t count);

DLL void rf24_setChannel(RF24Handle rf_handle, uint8_t channel);

DLL uint8_t rf24_getChannel(RF24Handle rf_handle);

DLL void rf24_setPayloadSize(RF24Handle rf_handle, uint8_t size);

DLL uint8_t rf24_getPayloadSize(RF24Handle rf_handle);

DLL uint8_t rf24_getDynamicPayloadSize(RF24Handle rf_handle);

DLL void rf24_enableAckPayload(RF24Handle rf_handle);

DLL void rf24_enableDynamicPayloads(RF24Handle rf_handle);

DLL void rf24_disableDynamicPayloads(RF24Handle rf_handle);

DLL void rf24_enableDynamicAck(RF24Handle rf_handle);

DLL cbool rf24_isPVariant(RF24Handle rf_handle);

DLL void rf24_setAutoAck(RF24Handle rf_handle, cbool enable);

DLL void rf24_setAutoAck_pipe(RF24Handle rf_handle, uint8_t pipe, cbool enable);

DLL void rf24_setPALevel(RF24Handle rf_handle, rf24_pa_dbm_val level);

DLL rf24_pa_dbm_val rf24_getPALevel(RF24Handle rf_handle);

DLL cbool rf24_setDataRate(RF24Handle rf_handle, rf24_datarate_val speed);

DLL rf24_datarate_val rf24_getDataRate(RF24Handle rf_handle);

DLL void rf24_setCRCLength(RF24Handle rf_handle, rf24_crclength_val length);

DLL rf24_crclength_val rf24_getCRCLength(RF24Handle rf_handle);

DLL void rf24_disableCRC(RF24Handle rf_handle);

DLL void rf24_maskIRQ(RF24Handle rf_handle, cbool tx_ok, cbool tx_fail, cbool rx_ready);


