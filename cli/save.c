#include "cli.h"

/**
 * cli_save - program that saves the current state of the blockchain
 * to a file specified by the user
 *
 * this function validates the number of command-line arguments passed
 * and attempts to serialize the blockchain data into a file
 *
 * @state: a pointer to the state_t structure containing blockchain
 *         information and command-line arguments
 *
 * Return : - EXIT_SUCCESS if the blockchain was successfully saved,
 *          - otherwise EXIT_FAILURE after setting the state's status
 *            to 2 if there are too many or too few arguments
 */

int save(state_t *state)
{
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

	if (blockchain_serialize(state->blockchain, state->argv[1]) == -1)
	{
		fprintf(stdout, "Failed to save blockchain to %s\n",
			state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}

	fprintf(stdout, "Saved blockchain to %s\n",
		state->argv[1]);

	return ((state->status = EXIT_SUCCESS));
}
