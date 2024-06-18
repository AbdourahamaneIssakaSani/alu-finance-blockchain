#include "cli.h"

/**
 * cli_wallet_load - program that loads a wallet based on
 * the command-line arguments provided
 *
 * this function attempts to load a wallet file from a specified path,
 * validates the number of input arguments, and handles errors appropriately
 *
 * @state: the state structure containing command-line arguments and program state
 *
 * Return: an integer indicating the exit status,
 *         EXIT_SUCCESS on successful wallet load,
 *         otherwise EXIT_FAILURE
 */

int load_wallet(state_t *state)
{
	EC_KEY *wallet = NULL;

	if (state->argc > 2)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}

	if (state->argc < 2)
	{
		fprintf(stderr, "%s: too few arguments\n", state->argv[0]);
		return ((state->status = 2));
	}

	wallet = ec_load(state->argv[1]);

	if (!wallet)
	{
		fprintf(stdout, "Failed to load wallet from %s\n",
			state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}

	EC_KEY_free(state->wallet);
	state->wallet = wallet;
	fprintf(stdout, "Loaded wallet from %s\n",
		state->argv[1]);

	return ((state->status = EXIT_SUCCESS));
}
