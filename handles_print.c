#include "shell.h"

/**
 * print_error - prints an error message
 * @info: param & return info struct
 * @es: string that contains the specified error type
 *
 * Return: 0 if there are no numbers in string, or -1 if otherwise
 */

void print_error(info_t *info, char *es)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(es);
}

/**
 * print_d - function that prints a decimal number (int base 10)
 * @in: input
 * @fd: file descriptor to be written to
 *
 * Return: number of chars printed
 */

int print_d(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int s, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		count++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (s = 1000000000; s > 1; s /= 10)
	{
		if (_abs_ / s)
		{
			__putchar('0' + current / s);
			count++;
		}
		current %= s;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * _erratoi - converts a string to an integer
 * @s: string to be converted
 *
 * Return:
 * 0 if there are no numbers in string & -1 otherwise
 */

int _erratoi(char *s)
{
	int a = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (a = 0; s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			result *= 10;
			result += (s[a] = '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * convert_number - converter function, itoa clone
 * @no: number
 * @base: base
 * @fl: arg flags
 *
 * Return: the string
 */

char *convert_number(long int no, int base, int fl)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *p;
	unsigned long n = no;

	if (!(fl & CONVERT_UNSIGNED) && no < 0)
	{
		n = -no;
		sign = '-';
	}
	array = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--p = sign;
	return (p);
}

/**
 * remove_comments - function that replaces the first instance of '#' with '\0'
 * @buf: adr of the string to be modified
 *
 * Return: 0 if successful
 */

void remove_comments(char *buf)
{
	int m;

	for (m = 0; buf[m] != '\0'; m++)
		if (buf[m] == '#' && (!m || buf[m - 1] == ' '))
		{buf[m] = '\0';
			break;
		}
}
