#include "shell.h"
/**
 * sort_line - sorts a string by using tokenization with
 * space as a delimiter
 * @string: string
 *
 * Return: pointer to string
 */
char **sort_line(char *string)
{
	char **args;
	char *token, *new_str;
	int i = 0, s = 0;

	if (string == NULL)
		return (NULL);

	string = no_newline(string);
	new_str = _strdup(string);
	token = strtok(string, " ");

	while (token != NULL)
	{
		s++;
		token = strtok(NULL, " ");
	}

	args = (char **)malloc(sizeof(char *) * (s + 1));
	if (!args)
		return (NULL);

	token = strtok(new_str, " ");

	while (token != NULL)
	{
		args[i] = _strdup(token);
		token = strtok(NULL, " ");
		i++;
	}

	args[i] = NULL;

	free(new_str);

	return (args);
}

/**
 * no_newline - this function removes a newline character
 * @string: pointer to a string
 *
 * Return: pointer to new string
 */
char *no_newline(char *string)
{
	char *sub_str = string;

	if (!string)
		return (NULL);

	sub_str = strtok(sub_str, "\n");
	return (sub_str);
}

/**
 * _strlen - this function finds the length of a string
 * @string: pointer to the string to be measured
 *
 * Return: length of string
 */
size_t _strlen(const char *string)
{
	const char *length = string;

	while (*string != '\0')
	{
		string++;
	}

	return ((size_t) (string - length));
}

/**
 * _strdup - this function duplicates a string
 * @string: string to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	char *dup_string;
	int i, len;

	if (string == NULL)
		return (NULL);

	len = _strlen(string) + 1;
	dup_string = malloc(len);

	if (dup_string == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		dup_string[i] = string[i];

	return (dup_string);
}
