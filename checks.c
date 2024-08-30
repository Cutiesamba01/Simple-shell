#include "shell.h"

/**
 * interactive - checks if the shell is interactive
 * @info: struct adr
 *
 * Return: 0 if true and 1 if otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimiter
 * @f: chararcter to be checked
 * @delimit: delimiter string
 *
 * Return: 0 if true and 1 if otherwise
 */

int is_delim(char f, char *delimit)
{
	while (*delimit)
		if (*delimit++ == f)
			return (0);
	return (1);
}

/**
 * _isalpha - checks for alphabetic characters
 * @u: character to be inputted
 *
 * Return: 0 if true and 1 if otherwise
 */

int _isalpha(int u)
{
	if ((u >= 'a' && u <= 'z') || (u >= 'A' && u <= 'Z'))
		return (0);
	else
		return (1);
}

/**
 * _atoi - converts string to integer
 * @s: string to be converted
 *
 * Return: 0 if conversion happened and 1 otherwise
 */

int _atoi(char *s)
{
	int t, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (t = 0; s[t] != '\0' && flag != 2; t++)
	{
		if (s[t] == '-')
			sign *= -1;
		if (s[t] >= '0' && s[t] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
