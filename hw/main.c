#include "main.h"


int rx_callback(hackrf_transfer* transfer)
{
	for (int i = 0; i < transfer->valid_length; i++)
	{
		printf("%x ", transfer->buffer[i]);
	}
	return 0;
}


void start_rx()
{
	if (!rf_start_rx(rx_callback))
		return;
	signal(SIGINT, rf_stop_rx);

	while (rf_get_current_rf_mode() & RF_MODE_RX)
		sleep(1);
}


int tx_callback(hackrf_transfer* transfer)
{
	memset(transfer->buffer, 0, transfer->valid_length);
	return 0;
}


void start_tx()
{
	if (!rf_start_tx(tx_callback))
		return;
	signal(SIGINT, rf_stop_tx);

	while (rf_get_current_rf_mode() & RF_MODE_TX)
		sleep(1);
}


int main()
{
	if (!rf_initialize())
		return 0;

	

	rf_release();
	return 0;
}
