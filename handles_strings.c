#include "shell.h"

/**
 * _strlen - returns length of string
 * @s: string whose length is to be checked
 *
 * Return: length of string (int)
 */

int _strlen(char *s)
{
	int f = 0;

	if (!s)
		return (0);
	while (*s++)
		f++;
	return (f);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: negative if s1 < s2 / positive if s1 > s2 / 0if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to saerch
 * @needle: substring to find
 *
 * Return: adr of haystack next char / NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @des: destination buffer
 * @src: source buffer
 *
 * Return: pointer to destination buffer
 */

char *_strcat(char *des, char *src)
{
	char *ret = des;

	while (*des)
		des++;
	while (*src)
		*des++ = *src++;
	*des = *src;
	return (ret);
}
