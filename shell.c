#include "shell.h"
/**
 * main - check the code
 * @argc: The argument count
 * @argv: The argument vector
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	prompt();
	while (1)
	{
		execute_cmd(argc, argv);
	}

	return (0);
}
