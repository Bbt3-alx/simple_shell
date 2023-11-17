#include "shell.h"

/**
 * print - print a string like printf
 * @str: The string to be printing
 * Return: The number of character printed
 */
int print(const char *str)
{
	int len, len_write;

	if (str == NULL)
		return (0);

	len = strlen(str);
	len_write = write(STDOUT_FILENO, &str, len);

	return (len_write);
}
