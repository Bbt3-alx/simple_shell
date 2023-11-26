#include "shell.h"
/**
 * execute_cmd - execute the command entered by the user
 * @argc: The argument count
 * @argv: the argument count
 * Return: Status code
 */
int execute_cmd(int __attribute__ ((unused)) argc, char **argv)
{
	/* Variable declaration */
	char **tokens = NULL;
	char *path_copy = NULL;
	char *full_path = NULL;
	int status, i = 0, exit_status;
	pid_t pid;

	tokens = tokenize_input();

	/* Tokenize the PATH variable */

	if (i > 0)
		tokens[i - 1][strlen(tokens[i - 1]) - 1] = '\0'; /* Remove the new line */

	/* Handle builtin commands */
	if (strcmp(tokens[0], "exit") == 0)
	{
		if (tokens[1])
		{
			exit_status = atoi(tokens[1]);
			free_tokens(tokens);
			exit(exit_status);
		}
		else
		{
			free_tokens(tokens);
			exit(0);
		}
	}
	else if (strcmp(tokens[0], "env") == 0)
	{
		free_tokens(tokens);
		print(getenv("PATH"));
	}
	else if (strcmp(tokens[0], "cd") == 0)
	{
		if (tokens[1])
		{
			/* Check if the directory exists */
			if (chdir(tokens[1]) < 0)
			{
				free_tokens(tokens);
				perror("chdir");
			}
		}
		else
		{
			if (chdir(".") < 0)
			{
				free_tokens(tokens);
				perror("chdir");
			}
		}

	}
	else
	{

		full_path = get_cmd(tokens);

		if (full_path == NULL)
		{
			/*fprintf(stderr, "%s: %d: %s: not found\n", argv[0], i, tokens[0]);*/
			free_tokens(tokens);
			prompt();
			return (1); /* Return an error code */
		}

		/* Check if a cmd has been entered */
		if (strlen(tokens[0]) == 0)
		{
			free(full_path);
			free_tokens(tokens);
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
					exit(EXIT_FAILURE);
				}
			}
			else if (pid < 0)
			{
				perror("fork");
				free(full_path);
				free_tokens(tokens);
				return (1); /* Return an error code */
			}
			else
			{
				/* Wait for the child process to finish */
				if (waitpid(pid, &status, 0) == -1)
				{
					free(full_path);
					free_tokens(tokens);
					perror("waitpid");
				}
				free(full_path);
				free_tokens(tokens);
			}
		}

	}
	/*free_tokens(tokens);*/
	if (path_copy != NULL)
		free(path_copy);
	/* Display the prompt again */
	prompt();
	return (0);
}
