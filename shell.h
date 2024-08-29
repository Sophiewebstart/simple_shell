#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/stat.h>

extern char **environ;

char *no_newline(char *string);
size_t _strlen(const char *string);
char *_strdup(const char *string);
char **sort_line(char *string);
void sig_stop(int sign_no);
int main(int ac __attribute__((unused)), char *av[]);
void exec_pid(char **argv);
void __free(char **my_memory);
int find_builtin(char **argv, int stat, char *line);
int __atoi(const char *string);
int _strcmp(const char *s1, const char *s2);
char *path_construct(char *cmd_line);
char *get_env(const char *name);
char *_strncpy(char *dest, const char *src, int n);
char *_strncat(char *dest, const char *src, int n);
char *path_finder(const char *pth_token, const char *cmd_line);

#endif
