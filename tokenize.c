#include "shell.h"
/**
 * tokenize_input - Tokenize the commande from the user
 * @line: The user input will be stored in this variable
 * @cmd_size: The size of the array of tokens
 * Return: Nothing.
 */
char **tokenize_input(char *line, int cmd_size)
{
	/* Tokenize the command */
	char *token = NULL;
	char **tokens = NULL;
	int i = 0;

	tokens = (char **)malloc((cmd_size + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		perror("malloc");
		free(line);
		return (NULL); /* Handle error gracefully */
	}

	/* Tokenize the command */
	token = strtok(line, " ");
	while (token != NULL)
	{
		tokens[i] = (char *)malloc(strlen(token) + 1);

		if (tokens[i] == NULL)
		{
			perror("malloc");
			free_tokens(tokens, i);
			free(line);
			return (NULL); /* Handle error gracefully */
		}
		strncpy(tokens[i], token, strlen(token) + 1);
		i++;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL; /* Append NULL at the end */

	return (tokens);
}
