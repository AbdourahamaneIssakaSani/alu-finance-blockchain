#include "cli.h"

/**
 * state_clear - program that clears the state of the application
 *
 * this function resets all elements of the state structure to their initial values;
 * it frees memory allocations and sets pointers to NULL to avoid dangling references
 *
 * @state: a pointer to the state structure to be cleared
 *
 * Return: nothing (void)
 */

void state_clear(state_t *state)
{
	state->argc = 0;
	free(state->argv);
	state->argv = NULL;
	free(state->line);
	state->line = NULL;
	state->linesz = 0;
	EC_KEY_free(state->wallet);
	state->wallet = NULL;
	blockchain_destroy(state->blockchain);
	state->blockchain = NULL;
	llist_destroy(state->tx_pool, 1, (node_dtor_t)transaction_destroy);
	state->tx_pool = NULL;
}
