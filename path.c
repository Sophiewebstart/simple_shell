#include "shell.h"
/**
 * path_construct - gets the path of a program
 * @cmd_line: commands to be passed
 *
 * Return:path
 */
char *path_construct(char *cmd_line)
{
	char *path, *path_dups, *pth_token, *file_path;
	struct stat string;

	if (!cmd_line)
		return (NULL);

	if (stat(cmd_line, &string) == 0)
		return (cmd_line);

	path = get_env("PATH");

	if (!path)
		return (NULL);

	path_dups = _strdup(path);
	pth_token = strtok(path_dups, ":");

	while (pth_token != NULL)
	{
		file_path = path_finder(pth_token, cmd_line);

		if (stat(file_path, &string) == 0)
		{
			free(path_dups);
			return (file_path);
		}
		else
		{
			free(file_path);
			pth_token = strtok(NULL, ":");
		}
	}

	free(path_dups);
	return (NULL);
}

/**
 * get_env - this function gets environmental variable
 * @name: name of first few char for variable
 *
 * Return: string
 */
char *get_env(const char *name)
{
	int t;
	char *token;

	if (!name)
		return (NULL);

	t = 0;
	while (environ[t])
	{
		token = strtok(environ[t], "=");

		if  (_strcmp(token, name) == 0)
		{
			return (strtok(NULL, "="));
		}
		t++;
	}
	return (NULL);
}

/**
 * path_finder - gets the path of the prrogram
 * @cmd_line: command
 * @pth_token: tokenized path
 *
 * Return: path
 */
char *path_finder(const char *pth_token, const char *cmd_line)
{
	char *file_path;
	int length, j = 0;

	if (!pth_token || !cmd_line)
		return (NULL);

	length = _strlen(pth_token) + _strlen(cmd_line) + 2;
	file_path = malloc(sizeof(char) * length);

	if (file_path == NULL)
		return (NULL);

	while (j < length)
	{
		file_path[j] = 0;
		j++;
	}

	file_path[length - 1] = 0;

	file_path = _strncpy(file_path, pth_token, _strlen(pth_token));
	file_path = _strncat(file_path, "/", 1);
	file_path = _strncat(file_path, cmd_line, _strlen(cmd_line));

	return (file_path);
}

 /**
  * _strncpy - this function copies a string into another string
  * @dest: string to be copied to
  * @src: string being copied
  * @n: number of bytes to be copied
  *
  * Return: destination string
  */
char *_strncpy(char *dest, const char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	for ( ; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (dest);
}

/**
  * _strncat - this concatenates two strings using at most n bytes from src
  * @dest: string to be appended to
  * @src: string being appended
  * @n: number of bytes from src being used
  *
  * Return: A pointer to the resulting string dest.
  */
char *_strncat(char *dest, const char *src, int n)
{
	char *f = dest;

	while (*f != '\0')
	{
		f++;
	}

	while (*src != '\0' && n > 0)
	{
		*f = *src;
		f++;
		src++;
		n--;
	}
	*f = '\0';
	return (dest);
}
