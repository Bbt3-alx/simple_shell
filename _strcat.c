#include "shell.h"

/**
 * _strcat - concatenate two srings
 * @destination: Where the string is to be added
 * @source: The string to be added
 * Return: An array of characeter
 */

char *_strcat(char *destination, char *source)
{
	int dest_len = 0;
	int i = 0, j = 0;
	int src_len = 0;
	char *result;

	if (destination == NULL)
		destination = "";
	if (source == NULL)
		source = "";

	while (destination[i] != '\0')
	{
		dest_len++;
		i++;
	}

	while (source[j] != '\0')
	{
		src_len++;
		j++;
	}

	result = (char *)malloc(dest_len + src_len + 1);
	if (result == NULL)
	{
		return (NULL);
		free(result);
	}

	result[0] = '\0';
	for (i = 0; i < dest_len; i++)
		result[i] = destination[i];

	for (i = 0; i < src_len; i++)
		result[dest_len + i] = source[i];
	result[dest_len + src_len] = '\0';

	return (result);
}
