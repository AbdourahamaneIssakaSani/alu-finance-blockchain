#include "cli.h"

/**
 * executeCmd - program that attempts to execute a command
 * based on the first argument in state
 *
 * - if the command is found, it executes the command's associated function
 * - if the command is not found, it prints an error message and returns -1
 *
 * @state: contains the current command and its arguments
 *
 * Return: the result of the command function if found, otherwise -1
 */

static int executeCmd(state_t *state)
{
	command_t const *command = find_command(state->argv[0]);

	if (command)
		return (command->func(state));

	fprintf(stderr, "%s: command not found\n", state->argv[0]);

	return (-1);
}



/**
 * tokenize - program that splits the input line into tokens
 * based on spaces and updates the state with the tokens
 * as arguments for command execution
 *
 * @state: the state containing the line to tokenize and storage for tokens
 *
 * Return: nothing (void)
 */

static void tokenize(state_t *state)
{
	char *lined_up = strdup(state->line);
	char **tokens = NULL;
	char *token = NULL;
	int ntokens = 0;

	state->argc = 0;
	state->argv = NULL;

	if (lined_up)
	{
		token = strtok(lined_up, BLANK);

		if (token)
		{
			do {
				ntokens += 1;
				token = strtok(NULL, BLANK);
			} while (token);
		}
		free(lined_up);

		tokens = calloc(ntokens + 1, sizeof(*tokens));
		ntokens = 0;
		token = strtok(state->line, BLANK);

		if (token)
		{
			do {
				tokens[ntokens] = token;
				ntokens += 1;
				token = strtok(NULL, BLANK);
			} while (token);
		}
		state->argc = ntokens;
		state->argv = tokens;
	}
}



/**
 * main - the entry point
 *
 * main program that initializes the program state,
 * continuously reads user input, tokenizes it,
 * and attempts to execute commands until termination
 *
 * Return: the final status code of the program execution
 */

int main(void)
{
	state_t state = {0};
	ssize_t nread = 0;
	int status = 0;

	state_init(&state);

	while (1)
	{
		printf("%s", PROMPT);
		nread = getline(&state.line, &state.linesz, stdin);

		if (nread < 1)
		{
			printf("\n");
			break;
		}
		tokenize(&state);

		if (state.argv && state.argc > 0)
			state.status = executeCmd(&state);

		free(state.argv);
		state.argc = 0;
		state.argv = NULL;
	}
	status = state.status;
	state_clear(&state);

	return (status);
}
