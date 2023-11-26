#include "shell.h"
/**
 * get_cmd - get the command from user input
 * @tokens: The array of token
 * Return: The full path of the file
 */
char *get_cmd(char **tokens)
{
	char *full_path = NULL;
	char *path_token;
	struct stat st;
	char *path_copy;

		/* Iterate through PATH directories */
	
	/* Get a copy of the PATH variable */
	path_copy = strdup(getenv("PATH"));
	if (path_copy == NULL)
	{
		perror("strdup");
		free_tokens(tokens);
		return (NULL);
	}

	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		/* Allocate memory for full_path */
		full_path = malloc(strlen(path_token) + strlen(tokens[0]) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free_tokens(tokens);
			return (NULL); /* Handle error gracefully */
		}

		/* Concatenate path and command with a forward slash */
		strcpy(full_path, path_token);
		strcat(full_path, "/");
		strcat(full_path, tokens[0]);

		/* Check if the file exists */
		if (access(full_path, X_OK) == 0 && stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		/* Get the next directory from PATH */
		path_token = strtok(NULL, ":");

	}
	free(path_copy);
	return (NULL);
}
