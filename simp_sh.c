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
	int stat = 0;
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
			__free(argv);
			continue;
		}

		if (find_builtin(argv, stat, line) == 1)
			continue;

		exec_pid(argv);
		__free(argv);
	}
	return (0);
}

/**
 * exec_pid - this function executes a command
 * @argv: array of arguments
 */
void exec_pid(char **argv)
{
	pid_t mypid;
	int stat;
	char *new_cmd = NULL;

	mypid = fork();
	if (mypid == -1)
	{
		perror("no fork");
		return;
	}

	else if (mypid == 0)
	{
		new_cmd = path_construct(argv[0]);
		if (!new_cmd)
		{
			perror("cmd not here");
			exit(EXIT_SUCCESS);
		}

		if (execve(new_cmd, argv, environ) == -1)
		{
			perror("Wrong again");
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		/* parent process */
		waitpid(mypid, &stat, 0);
	}
	if (new_cmd != argv[0])
	{
		free(new_cmd);
	}
}

/**
 * __free - this function frees the memory of a double pointer
 * @my_memory: memory to be freed
 */
void __free(char **my_memory)
{
	char **tmp_mem;

	if (my_memory == NULL)
	{
		return;
	}

	tmp_mem = my_memory;

	while (*tmp_mem != NULL)
	{
		free(*tmp_mem);
		*tmp_mem = NULL;
		tmp_mem++;
	}

	free(my_memory);
}
