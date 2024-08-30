#include "shell.h"

/**
 * *_strncpy - copies a string
 * @des: destination the string is to be copied
 * @src: source string
 * @n: amount of chars to be copied
 *
 * Return: concatenated string
 */

char *_strncpy(char *des, char *src, int n)
{
	int b, r;
	char *s = des;

	b = 0;
	while (src[b] != '\0' && b < n - 1)
	{
		des[b] = src[b];
		b++;
	}
	if (b < n)
	{
		r = b;
		while (r < n)
		{
			des[r] = '\0';
			r++;
		}
	}
	return (s);
}

/**
 * *_strncat - concatenates two strings
 * @s1: first string
 * @s2: second string
 * @n: amount of bytes to be used
 *
 * Return: concatenated string
 */

char *_strncat(char *s1, char *s2, int n)
{
	int b, r;
	char *s = s1;

	b = 0;
	r = 0;
	while (s1[b] != '\0')
		b++;
	while (s2[r] != '\0' && r < n)
	{
		s1[b] = s2[r];
		b++;
		r++;
	}
	if (r < n)
		s1[b] = '\0';
	return (s);
}

/**
 * *_strchr - locates chr in string
 * @s: string to be parsed
 * @c: char to be located
 *
 * Return:npointer ro the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
