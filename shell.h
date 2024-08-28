#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

char *no_newline(char *string);
size_t _strlen(const char *string);
char *_strdup(const char *string);
char **sort_line(char *string);
void sig_stop(int sign_no);
int main(int ac __attribute__((unused)), char *av[]);
void exec_pid(char *cmd_line);

#endif
