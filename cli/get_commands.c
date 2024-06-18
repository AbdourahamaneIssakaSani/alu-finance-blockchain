#include "cli.h"

/**
 * get_commands - program that retrieves a list of command structures
 *
 * each command structure is defined with specific handlers, names,
 * help texts, and descriptions
 *
 * Return: a pointer to an array of command_t structures;
 *         the array is terminated by a NULL entry
 */

command_t const *get_commands(void)
{
	static command_t commands[] = {
		{help, HELP_NAME, HELP_HELP, HELP_DESCRIPTION},
		{create_blockchain, CREATE_BLOCKCHAIN_NAME, CREATE_BLOCKCHAIN_HELP, CREATE_BLOCKCHAIN_DESCRIPTION},
		{print_blockchain, PRINT_BLOCKCHAIN_NAME, PRINT_BLOCKCHAIN_HELP, PRINT_BLOCKCHAIN_DESCRIPTION},
		{mine_block, MINE_BLOCK_NAME, MINE_BLOCK_HELP, MINE_BLOCK_DESCRIPTION},
		{info_tx, INFO_TX_NAME, INFO_TX_HELP, INFO_TX_DESCRIPTION},
		{load, LOAD_NAME, LOAD_HELP, LOAD_DESCRIPTION},
		{save, SAVE_NAME, SAVE_HELP, SAVE_DESCRIPTION},
		{transaction_add, ADD_TRANSACTION_NAME, ADD_TRANSACTION_HELP, ADD_TRANSACTION_DESCRIPTION},
		{load_wallet, WALLET_LOAD_NAME, WALLET_LOAD_HELP, WALLET_LOAD_DESCRIPTION},
		{save_wallet, WALLET_SAVE_NAME, WALLET_SAVE_HELP, WALLET_SAVE_DESCRIPTION},
		{exit_program, EXIT_NAME, EXIT_HELP, EXIT_DESCRIPTION},
		{NULL, NULL, NULL, NULL}
	};

	return (commands);
}

