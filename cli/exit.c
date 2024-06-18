#include "cli.h"

/**
 * cli_exit - program that terminates the command-line interface cleanly
 *
 * this function checks if the number of arguments exceeds one and displays
 * an error if so;
 * it then clears the command-line state and exits the program successfully
 *
 * @state: a pointer to the state structure holding the CLI context
 *
 * Return: EXIT_FAILURE on error (too many arguments),
 *         otherwise it exits the program with EXIT_SUCCESS
 */

int exit_program(state_t *state)
{
	if (state->argc > 1)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return (EXIT_FAILURE);
	}
	state_clear(state);

	exit(EXIT_SUCCESS);
}
