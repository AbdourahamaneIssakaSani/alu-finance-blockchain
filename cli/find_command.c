#include "cli.h"

/**
 * find_command - program that finds a command in the command list
 * that matches the specified name
 *
 * @name: the name of the command to find
 *
 * Return: a pointer to the command if found, otherwise NULL
 */

command_t const *find_command(char const *name)
{
	command_t const *command = get_commands();

	while (command->name)
	{
		if (strcmp(name, command->name) == 0)
			return (command);
		command += 1;
	}
	return (NULL);
}

