#include "shell.h"

/**
 * sig_stop - function for error handling
 *
 *@sign_no: voided
 */
void sig_stop(int sign_no)
{
	 (void) sign_no;

	 write(STDOUT_FILENO, "\n", 1);
	 write(STDOUT_FILENO, "#cshell($) ", 11);
}

/**
 * main - execution stage
 *
 * @ac: voided
 * @av: arguement vector
 *
 * Return: 0 on success
 */
int main(int ac __attribute__((unused)), char *av[])
{
	char *line = NULL;
	size_t buf = 0;
	char **argv = NULL;
	(void) av;

	signal(SIGINT, sig_stop);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cshell($) ", 11);

		if (getline(&line, &buf, stdin) == -1)
		{
			free(line);

			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);

			exit(EXIT_SUCCESS);
		}

		if (*line == '\n' || *line == '\0')
			continue;

		argv = sort_line(line);

		if (argv == NULL || argv[0] == NULL)
		{
			free(argv);
			continue;
		}

		 exec_pid(argv[0], argv);

		 free(argv);
	}
	return (0);
}

/**
 * exec_pid - this function executes a command
 * @cmd_line: command to be executed
 * @argv: array of arguments
 */
void exec_pid(char *cmd_line, char **argv)
{
	pid_t mypid;
	int stat;

	mypid = fork();
	if (mypid == -1)
	{
		perror("Error");
		return;
	}

	if (mypid == 0)
	{
		if (execve(cmd_line, argv, NULL) == -1)
		{
			perror("Error");
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		/* parent process */
		wait(&stat);
	}
}
