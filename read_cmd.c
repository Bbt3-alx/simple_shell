#include "shell.h"
/**
 * read_cmd - Reads a command from the user
 * @cmd_size: The size of the array of tokens
 * @tokens: A pointer to an array of tokens
 * @i: The index of token in tokens array
 * Return: Nothing
 */

void read_cmd(char ***tokens, int *cmd_size, int *i)
{
	/*variable declaration */
	char *line = NULL;
	size_t size = 0;

	/* Read the commande */
	*cmd_size = getline(&line, &size, stdin);

	if (*cmd_size == -1)
	{
		if (feof(stdin))
		{
			/* CTRL-D was pressed, exit the program */
			free_tokens(*tokens, *i);
			exit(0);
		}
		else
		{
			perror("getline");
			return; /* Handle error gracefullly */
		}
	}

	/* Tokenize the command */
	*tokens = tokenize_input(line, *cmd_size);

	for (*i = 0; (*tokens)[*i] != NULL; (*i)++)
	{
	}
}
