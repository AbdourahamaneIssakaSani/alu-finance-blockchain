#include "cli.h"

/**
 * state_init - program that initializes the state structure
 * with default values and create essential structures
 *
 * @state: a pointer to the state_t structure that will be initialized
 *
 * Return: nothing (void)
 */

void state_init(state_t *state)
{
	state->status = EXIT_SUCCESS;
	state->argc = 0;
	state->argv = NULL;
	state->line = NULL;
	state->linesz = 0;
	state->wallet = ec_create();
	state->blockchain = blockchain_create();
	state->tx_pool = llist_create(MT_SUPPORT_FALSE);
}
