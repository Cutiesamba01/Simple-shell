#include "shell.h"

/**
 * **strtow - splits a string into words, repeated delimiters are ignored
 * @str: input string
 * @d: delimeter string
 *
 * Return: pointer to an array of strings / NULL on failure
 */

char **strtow(char *str, char *d)
{
	int f, u, n, t, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (f = 0; str[f] != '\0'; f++)
		if (!is_delim(str[f], d) && (is_delim(str[f + 1], d) || !str[f + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (f = 0, u = 0; u < numwords; u++)
	{
		while (is_delim(str[f], d))
			f++;
		n = 0;
		while (!is_delim(str[f + n], d) && str[f + n])
			n++;
		s[u] = malloc((n + 1) * sizeof(char));
		if (!s[u])
		{
			for (n = 0; n < u; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (t = 0; t < n; t++)
			s[u][t] = str[f++];
		s[u][t] = 0;
	}
	s[u] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: input string
 * @d: delimeter
 *
 * Return: pointer to an array of strings / NULL on failure
 */

char **strtow2(char *str, char d)
{
	int f, u, n, t, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (f = 0; str[f] != '\0'; f++)
		if ((str[f] != d && str[f + 1] == d) ||
		    (str[f] != d && !str[f + 1]) || str[f + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (f = 0, u = 0; u < numwords; u++)
	{
		while (str[f] == d && str[f] != d)
			f++;
		n = 0;
		while (str[f + n] != d && str[f + n] && str[f + n] != d)
			n++;
		s[u] = malloc((n + 1) * sizeof(char));
		if (!s[u])
		{
			for (n = 0; n < u; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (t = 0; t < n; t++)
			s[u][t] = str[f++];
		s[u][t] = 0;
	}
	s[u] = NULL;
	return (s);
}
