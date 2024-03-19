#ifndef __RF_H__
#define __RF_H__


#include <libhackrf/hackrf.h>
#include <stdio.h>
#include <stdbool.h>
#include "logger.h"


#define RF_MODE_RX 2
#define RF_MODE_TX 4


bool rf_initialize();
bool rf_start_rx(int (*rx_callback)(hackrf_transfer* transfer));
void rf_stop_rx();
bool rf_start_tx(int (*tx_callback)(hackrf_transfer* transfer));
void rf_stop_tx();
uint16_t rf_get_current_rf_mode();
void rf_release();
bool rf_is_release();


#endif // __RF_H__
