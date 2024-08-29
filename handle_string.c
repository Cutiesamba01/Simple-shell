#include "shell.h"

/**
 * _strcpy - copies string
 * @des: destination buffer
 * @src: source buffer
 *
 * Return: des pointer
 */

char *_strcpy(char *des, char *src)
{
	int u = 0;

	if (des == src || src == 0)
		return (des);
	while (src[u])
	{
		des[u] = src[u];
		u++;
	}
	des[u] = 0;
	return (des);
}

/**
 * _strdup - duplicates string
 * @s: string to be duplicated
 *
 * Return: duplicated string pointer
 */

char *_strdup(const char *s)
{
	int len = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--s;
	return (ret);
}

/**
 * _puts - prints input string
 * @s: string to be printed
 *
 * Return: Nothing
 */

void _puts(char *s)
{
	int n = 0;

	if (!s)
		return;
	while (s[n] != '\0')
	{
		_putchar(s[n]);
		n++;
	}
}

/**
 * _putchar - writes char c to stdout
 * @c: char to print
 *
 * Return: 1 if successful / -1 on error, errno is set appropriately
 */

int _putchar(char c)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(1, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}
