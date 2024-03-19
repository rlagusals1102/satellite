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


void print_desc()
{
	printf("\n%s+------------------------------+\n", CYN);
	printf("|                              |\n");
	printf("|         [Satellite]          |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|     0: Quit      1: RX       |\n");
	printf("|     2: TX                    |\n");
	printf("|                              |\n");
	printf("+------------------------------+%s\n", RST);
}


int main()
{
	if (!rf_initialize())
		return 0;

	char cmd[128];
	print_desc();
	while (1)
	{
		signal(SIGINT, print_desc);
		printf("%s>>>%s ", GRN, RST);
		scanf("%s", cmd);

		if (strncmp(cmd, "0", sizeof(cmd)) == 0)
			break;
		else if (strncmp(cmd, "1", sizeof(cmd)) == 0)
		{
			start_rx();
			print_desc();
		}
		else if (strncmp(cmd, "2", sizeof(cmd)) == 0)
		{
			start_tx();
			print_desc();
		}
		else
			printf("%sCannot find command '%s'.%s\n", RED, cmd, RST);
	}

	rf_release();
	return 0;
}
