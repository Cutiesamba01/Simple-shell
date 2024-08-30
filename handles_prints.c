#include "shell.h"

/**
 * _eputchar - writes char (c) to stderr
 * @o: char to be printed
 *
 * Return: 0 if successful / -1 if there's an error
 */

int _eputchar(char o)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (o == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(2, buf, f);
		f = 0;
	}
	if (o != BUF_FLUSH)
		buf[f++] = o;
	return (1);
}

/**
 * _putfd - writes char (c) to a given fd
 * @c: char to be printed
 * @fd: file descriptor to be written to
 *
 * Return: 0 if successful / -1 if there's an error
 */

int _putfd(char c, int fd)
{
	static int u;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(fd, buf, u);
		u = 0;
	}
	if (c != BUF_FLUSH)
		buf[u++] = c;
	return (1);
}

/**
 * _eputs - prints an input string
 * @s: string to be printed
 *
 * Return: Void
 */

void _eputs(char *s)
{
	int n = 0;

	if (!s)
		return;
			while (s[n] != '\0')
			{
				_eputchar(s[n]);
				n++;
			}
}

/**
 * _putsfd - prints an input string
 * @s: string to be printed
 * @fd: file descriptor to be written to
 *
 * Return: number of chars put
 */

int _putsfd(char *s, int fd)
{
	int t = 0;

	if (!s)
		return (0);
	while (*s)
	{
		t += _putfd(*s++, fd);
	}
	return (t);
}
