#include "cli.h"

/**
 * load - program that loads a blockchain from a file
 * specified in the command-line arguments
 *
 * this function checks if the correct number of arguments is provided
 * (exactly one argument for the blockchain file path);
 *
 * - if the number of arguments is incorrect, it prints an error message and returns an error code (2)
 * - if the arguments are correct, it attempts to deserialize the blockchain from the provided file path
 * - if deserialization fails, it prints a failure message, destroys any existing blockchain in the state,
 *   and returns a failure status
 * - if successful, it updates the state with the new blockchain, prints a success message,
 *   and returns a success status (EXIT_SUCCESS)
 *
 * @state: the current state of the CLI, including command-line arguments and the blockchain
 *
 * Return: the exit status indicating success (EXIT_SUCCESS),
 *         or failure (any non-zero value, typically 2 or EXIT_FAILURE)
 */

int load(state_t *state)
{
	blockchain_t *blockchain = NULL;

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
	blockchain = blockchain_deserialize(state->argv[1]);

	if (!blockchain)
	{
		fprintf(stdout, "Failed to load blockchain from %s\n",
			state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}
	blockchain_destroy(state->blockchain);
	state->blockchain = blockchain;
	fprintf(stdout, "Loaded blockchain from %s\n",
		state->argv[1]);

	return ((state->status = EXIT_SUCCESS));
}
