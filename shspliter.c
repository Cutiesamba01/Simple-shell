#include "shell.h"

/**
 * **strtow - splits a string into words, repeated delimiters are ignored
 * @s: input string
 * @d: delimeter string
 *
 * Return: pointer to an array of strings / NULL on failure
 */

char **strtow(char *s, char *d)
{
	int f, u, n, t, numwords = 0;
	char **o;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (f = 0; s[f] != '\0'; f++)
		if (!is_delim(s[f], d) && (is_delim(s[f + 1], d) || !s[f + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	o = malloc((1 + numwords) * sizeof(char *));
	if (!o)
		return (NULL);
	for (f = 0, u = 0; u < numwords; u++)
	{
		while (is_delim(s[f], d))
			f++;
		n = 0;
		while (!is_delim(s[f + n], d) && s[f + n])
			n++;
		o[u] = malloc((n + 1) * sizeof(char));
		if (!o[u])
		{
			for (n = 0; n < u; n++)
				free(o[n]);
			free(o);
			return (NULL);
		}
		for (t = 0; t < n; t++)
			o[u][t] = s[f++];
		o[u][t] = 0;
	}
	o[u] = NULL;
	return (o);
}

/**
 * **strtow2 - splits a string into words
 * @s: input string
 * @d: delimeter
 *
 * Return: pointer to an array of strings / NULL on failure
 */

char **strtow2(char *s, char d)
{
	int f, u, n, t, numwords = 0;
	char **o;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (f = 0; s[f] != '\0'; f++)
		if ((s[f] != d && s[f + 1] == d) ||
		    (s[f] != d && !s[f + 1]) || s[f + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	o = malloc((1 + numwords) * sizeof(char *));
	if (!o)
		return (NULL);
	for (f = 0, u = 0; u < numwords; u++)
	{
		while (s[f] == d && s[f] != d)
			f++;
		n = 0;
		while (s[f + n] != d && s[f + n] && s[f + n] != d)
			n++;
		o[u] = malloc((n + 1) * sizeof(char));
		if (!o[u])
		{
			for (n = 0; n < u; n++)
				free(o[n]);
			free(o);
			return (NULL);
		}
		for (t = 0; t < n; t++)
			o[u][t] = s[f++];
		o[u][t] = 0;
	}
	o[u] = NULL;
	return (o);
}
