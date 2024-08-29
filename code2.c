#include "shell.h"

/**
 * find_builtin - this function checks for builtin
 * @argv: strings that has been tokenized
 * @stat: exit ststus
 * @line: line from the shell
 *
 * Return: 0 on success
 */
int find_builtin(char **argv, int stat, char *line)
{
	char **env = environ;

	if (_strcmp(argv[0], "exit") == 0)
	{
		if (argv[1] == NULL)
		{
			__free(argv);
			free(line);
			exit(stat);
		}

		stat = __atoi(argv[1]);
		__free(argv);
		free(line);

		exit(stat);
	}

	if (_strcmp(argv[0], "env") == 0)
	{
		while (*env != NULL)
		{
			write(1, *env, _strlen(*env));
			write(1, "\n", 1);

			env++;
		}

		__free(argv);

		return (1);
	}
	return (0);
}

/**
 * __atoi - this function converts a string to an integer
 * @string: string to be corrected
 *
 * Return: integer value of converted string
 */
int __atoi(const char *string)
{
	int sign = 1;
	int value = 0;

	while (*string++)
	{

		if (*string == '-')
			sign = -1;

		else if (*string >= '0' && *string <= '9')
			value = (value * 10) + (*string - '0');

		else if (value > 0)
			break;
	}

	return (value * sign);
}

/**
  * _strcmp - compares two strings
  * @s1: first string
  * @s2: second string
  *
  * Description - writes a program that compares two strings
  * using the function _strcmp
  *
  * Return: an integer greater than, equal to, or less than zero
  * accordingly as the string pointed to by s1 is greater than
  * equal to, or less than the string pointed to by s2.
  */
int _strcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0')
		{
			return (0);
		}
	}
	return (s1[i] - s2[i]);
}
