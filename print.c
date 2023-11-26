#include "shell.h"

/**
 * print - print a string like printf
 * @str: The string to be printing
 * Return: The number of character printed
 */
int print(const char *str)
{
	int len_write;

	if (str == NULL)
		return (0);
	len_write = puts(str);

	return (len_write);
}
