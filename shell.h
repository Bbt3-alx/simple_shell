#ifndef SHELL_H
#define SHELL_H
#define MAX_TOKENS 128
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int prompt(void);
int print(const char *str);
char *get_cmd(char **tokens, int i, char *p_token);

char *_strcat(char *destination, char *source);
int execute_cmd(int argc, char **argv);
void free_tokens(char **tokens, int size);
char **tokenize_input(char *line, int cmd_size);
void read_cmd(char ***tokens, int *cmd_size, int *i);

#endif /* SHELL */
