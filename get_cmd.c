#include "shell.h"
/**
 * get_cmd - get the command from user input
 * @tokens: The array of token
 * @i: token index
 * @p_token: Directories in the path
 * Return: The full path of the file
 */
char *get_cmd(char **tokens, int i, char *p_token)
{
	char *full_path;
	struct stat st;

		/* Iterate through PATH directories */

	while (p_token != NULL)
	{
		/* Allocate memory for full_path */
		full_path = malloc(strlen(p_token) + strlen(tokens[0]) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free_tokens(tokens, i);
			return (NULL); /* Handle error gracefully */
		}

		/* Concatenate path and command with a forward slash */
		strcpy(full_path, p_token);
		_strcat(full_path, "/");
		_strcat(full_path, tokens[0]);

		/* Check if the file exists */
		if (access(full_path, X_OK) == 0 && stat(full_path, &st) == 0)
			return (full_path);
		free(full_path);

		/* Get the next directory from PATH */
		p_token = strtok(NULL, ":");

	}
	return (NULL);
}
