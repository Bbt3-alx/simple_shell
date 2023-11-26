#include "shell.h"

/**
 * prompt - display a prompt and wait for the iuser to enter a cmd
 * Return: Nothing
 */
int prompt(void)
{
	char str_prompt[] = "$ ";
	int len;

	if (isatty(STDIN_FILENO))
		len = write(STDOUT_FILENO, &str_prompt, strlen(str_prompt));

	return (len);
}
