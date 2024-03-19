#include "rf.h"


const uint64_t FREQUENCY = 436326000;
const uint32_t LNAGAIN = 11;
const uint32_t VGAGAIN = 11;
const double BANDWIDTH = 1000000;


hackrf_device* device = NULL;
uint16_t current_rf_mode = 0;


bool rf_initialize()
{
	if (device != NULL)
		return true;

	int result = hackrf_init();
	if (result != HACKRF_SUCCESS)
	{
		PRINT_RF_ERROR(hackrf_init, result);
		return false;
	}

	result = hackrf_open(&device);
	if (result != HACKRF_SUCCESS)
	{
		PRINT_RF_ERROR(hackrf_open, result);
		return false;
	}

	result = hackrf_set_freq(device, FREQUENCY);
	if (result != HACKRF_SUCCESS)
	{
		PRINT_RF_ERROR(hackrf_set_freq, result);
		return false;
	}

	result = hackrf_set_lna_gain(device, LNAGAIN);
	result |= hackrf_set_vga_gain(device, VGAGAIN);
	result |= hackrf_set_txvga_gain(device, VGAGAIN);
	if (result != HACKRF_SUCCESS)
	{
		PRINT_RF_ERROR(hackrf_set_vga_gain, result);
		return false;
	}

	result = hackrf_set_baseband_filter_bandwidth(device, hackrf_compute_baseband_filter_bw(BANDWIDTH));
	result = hackrf_set_sample_rate(device, BANDWIDTH);
	if (result != HACKRF_SUCCESS)
	{
		PRINT_RF_ERROR(hackrf_set_sample_rate, result);
		return false;
	}

	PRINT_INFO("hackrf initialization completed");
	return true;
}


bool rf_start_rx(int (*rx_callback)(hackrf_transfer* transfer))
{
	int result = hackrf_start_rx(device, rx_callback, NULL);

	if (result != HACKRF_SUCCESS)
	{
		PRINT_RF_ERROR(hackrf_start_rx, result);
		return false;
	}
	
	current_rf_mode |= RF_MODE_RX;
	PRINT_INFO("hackrf started rx");
	return true;
}


void rf_stop_rx()
{
	if ((current_rf_mode & RF_MODE_RX) == 0)
		return;
	int result = hackrf_stop_rx(device);

	if (result == HACKRF_SUCCESS)
	{
		current_rf_mode ^= RF_MODE_RX;
		PRINT_INFO("hackrf stopped rx");
	}
}


bool rf_start_tx(int (*tx_callback)(hackrf_transfer* transfer))
{
	int result = hackrf_start_tx(device, tx_callback, NULL);

	if (result != HACKRF_SUCCESS)
	{
		PRINT_RF_ERROR(hackrf_start_tx, result);
		return false;
	}

	current_rf_mode |= RF_MODE_TX;
	PRINT_INFO("hackrf started tx");
	return true;
}


uint16_t rf_get_current_rf_mode()
{
	return current_rf_mode;
}


void rf_stop_tx()
{
	if ((current_rf_mode & RF_MODE_TX) == 0)
		return;
	int result = hackrf_stop_tx(device);

	if (result == HACKRF_SUCCESS)
	{
		current_rf_mode ^= RF_MODE_TX;
		PRINT_INFO("hackrf stopped tx");
	}
}


void rf_release()
{
	if (device == NULL)
		return;
	rf_stop_rx();
	rf_stop_tx();
	hackrf_close(device);
	hackrf_exit();
	device = NULL;
	PRINT_INFO("hackrf device released");
}


bool rf_is_release()
{
	return (device == NULL);
}
