#include "shell.h"
/**
 * free_tokens - free an array of tokens
 * @tokens: The array of the token to be freed
 * @size: The size of the tokens array
 * Return: Noting
 */
void free_tokens(char **tokens, int size)
{
	int i;

	for (i = 0; i < size; i++)
		free(tokens[i]);
	free(tokens);
}
