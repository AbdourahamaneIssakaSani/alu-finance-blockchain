#include "cli.h"

/**
 * sum_unspent_amounts - program that iterates over unspent
 * transaction outputs and accumulates their amounts
 *
 * this function is used to calculate the total unspent amount
 *
 * @node: a pointer to the unspent_tx_out_t structure
 *        (represents an unspent transaction output)
 * @idx: the index of the current item in the list (unused)
 * @arg: a pointer to a long unsigned int where the accumulated total is stored
 *
 * Return: 0 (success)
 */

static int sum_unspent_amounts(void *node,
			       unsigned int idx __attribute__((unused)), void *arg)
{
	unspent_tx_out_t *unspent_tx_out = node;
	unsigned long int *accumulator = arg;

	*accumulator += unspent_tx_out->out.amount;

	return (0);
}



/**
 * cli_info - program that provides a command line interface
 * summary of the blockchain state
 *
 * this function displays:
 * - the number of blocks,
 * - unspent transaction outputs,
 * - transactions in the pool,
 * - total coins
 *
 * @state: a pointer to the state_t structure
 *         containing all blockchain information
 *
 * Return: EXIT_SUCCESS on successful execution,
 *         or 2 if there are too many arguments
 */

int print_blockchain(state_t *state)
{
	unsigned long int coins = 0;

	if (state->argc > 1)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	_blockchain_print(state->blockchain);
	llist_for_each(state->blockchain->unspent, sum_unspent_amounts, &coins);

	fprintf(stdout, "Blocks:  %d\n",
		llist_size(state->blockchain->chain));
	fprintf(stdout, "Unspent: %d\n",
		llist_size(state->blockchain->unspent));
	fprintf(stdout, "Transactions: %d\n",
		llist_size(state->tx_pool));
	fprintf(stdout, "Coins:   %lu\n", coins);

	return ((state->status = EXIT_SUCCESS));
}
