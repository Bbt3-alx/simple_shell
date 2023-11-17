#include "shell.h"
/**
 * execute_cmd - execute the command entered by the user
 * @argc: The argument count
 * @argv: the argument count
 * Return: Status code
 */
int execute_cmd(int argc, char **argv)
{
	/* Variable declaration */
	char **tokens = NULL;
	char *path_copy;
	char *path_token;
	char *full_path = NULL;
	int status, i = 0, cmd_size = 0, exit_status;
	pid_t pid;

	if (argc < 1)
		return (0);

	read_cmd(&tokens, &cmd_size, &i);

	/* Get a copy of the PATH variable */
	path_copy = strdup(getenv("PATH"));
	if (path_copy == NULL)
	{
		perror("strdup");
		free_tokens(tokens, i);
		free(path_copy);
		return (1); /* Return an error code */
	}

	/* Tokenize the PATH variable */
	path_token = strtok(path_copy, ":");

	if (i > 0)
		tokens[i - 1][strlen(tokens[i - 1]) - 1] = '\0'; /* Remove the new line */

	/* Handle builtin commands */
	if (strcmp(tokens[0], "exit") == 0)
	{
		if (tokens[1])
		{
			exit_status = atoi(tokens[1]);
			exit(exit_status);
		}
		else
			exit(0);
	}
	else if (strcmp(tokens[0], "env") == 0)
		print(getenv("PATH"));
	else if (strcmp(tokens[0], "cd") == 0)
	{
		if (tokens[1])
		{
			/* Check if the directory exists */
			if (chdir(tokens[1]) < 0)
				perror("chdir");
		}
		else
		{
			if (chdir(".") < 0)
				perror("chdir");
		}
	}
	else
	{

		full_path = get_cmd(tokens, i, path_token);
		if (full_path == NULL)
		{
			print("Command not found");
			return (1); /* Return an error code */
		}

		/* Check if a cmd has been entered */
		if (strlen(tokens[0]) == 0)
		{
			prompt();
			return (0); /* Return success */
		}
		else
		{
			/* Fork a child process */

			pid = fork();
			if (pid == 0)
			{
				/* Child process executes the command */
				if (execvp(tokens[0], tokens) < 0)
				{
					fprintf(stderr, "%s: %d: %s: not found\n", argv[0], i, tokens[0]);
					free(full_path);
					free_tokens(tokens, i);
					exit(EXIT_FAILURE);
				}
			}
			else if (pid < 0)
			{
				perror("fork");
				free(full_path);
				free_tokens(tokens, i);
				return (1); /* Return an error code */
			}
			else
			{
				/* Wait for the child process to finish */
				if (waitpid(pid, &status, 0) == -1)
					perror("waitpid");
				prompt();
				return (0); /* Return success */
			}
		}

		free(full_path);
		path_token = strtok(NULL, ":");
	}
	free_tokens(tokens, i);
	free(path_copy);
	/* Display the prompt again */
	prompt();
	return (0);
}
