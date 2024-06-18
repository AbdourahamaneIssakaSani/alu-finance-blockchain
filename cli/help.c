#include "cli.h"

/**
 * cli_help - program that provides help information for commands
 * in the command-line interface
 *
 * @state: a pointer to the state_t structure containing the CLI state,
 *         including arguments
 *
 * Return: - an integer status code,
 *         - 2 if there are too many arguments,
 *         - EXIT_SUCCESS if the help for a command is displayed successfully,
 *         - EXIT_FAILURE if the command is not found
 */

int help(state_t *state)
{
	command_t const *command = NULL;

	if (state->argc > 2)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	if (state->argc > 1)
	{
		command = find_command(state->argv[1]);

		if (command)
		{
			fprintf(stdout, "usage: %s\n%s\n",
				command->help, command->desc);
			return ((state->status = EXIT_SUCCESS));
		}
		fprintf(stderr, "%s: %s: command not found\n",
			state->argv[0], state->argv[1]);

		return ((state->status = EXIT_FAILURE));
	}
	command = get_commands();

	while (command->name)
	{
		fprintf(stdout, "%s\n", command->help);
		command += 1;
	}
	return ((state->status = EXIT_SUCCESS));
}
