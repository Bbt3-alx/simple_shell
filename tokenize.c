#include "shell.h"
/**
 * tokenize_input - Tokenize the commande from the user
 * Return: The tokenized cmd.
 */
char **tokenize_input()
{
	/* Variable declaration */
	char *line = NULL;
	char *token = NULL;
	char **tokens = NULL;
	ssize_t cmd_size = 0;
	size_t size = 0;
	int i = 0;

	cmd_size = getline(&line, &size, stdin);
	if (cmd_size == -1)
	{
		if (feof(stdin))
		{
			free(line);
			/* write(STDOUT_FILENO, "\n", 1); */
			exit(0);
			return (NULL);
		}
		else
		{
			perror("getline");
			exit(1);
		}
	}
	/* Allocate memory for tokens */
	tokens = malloc((cmd_size + 1) * sizeof(char *));
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
			free_tokens(tokens);
			return (NULL);
		}
		strncpy(tokens[i], token, strlen(token) + 1);
		i++;
		token = strtok(NULL, " ");
	}
	if (i > 0)
		tokens[i - 1][strlen(tokens[i - 1]) - 1] = '\0'; /* remove the new line */

	free(line);
	return (tokens);
}
