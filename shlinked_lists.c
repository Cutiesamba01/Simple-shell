#include "shell.h"

/**
 * list_len - determines the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of list
 */

size_t list_len(const list_t *h)
{
	size_t r = 0;

	while (h)
	{
		h = h->next;
		r++;
	}
	return (r);
}

/**
 * list_to_strings - returns an array of strings of the list->s
 * @h: pointer to the first node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t f = list_len(h), o;
	char **ss;
	char *s;

	if (!h || !f)
		return (NULL);
	ss = malloc(sizeof(char *) * (f + 1));
	if (!ss)
		return (NULL);
	for (f = 0; node; node = node->next, f++)
	{
		s = malloc(_strlen(node->s) + 1);
		if (!s)
		{
			for (o = 0; o < f; o++)
				free(ss[o]);
			free(ss);
			return (NULL);
		}
		s = _strcpy(s, node->s);
		ss[f] = s;
	}
	ss[f] = NULL;
	return (ss);
}

/**
 * print_list - prints all elements of the list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t s = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * node_starts_with - returns the node whose string starts with prefix
 * @node: pointer to the haed of the list
 * @prefix: string to be matched
 * @c: the next char after prefix to match
 *
 * Return: match node / null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->s, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @h: pointer to the head of the list
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *h, list_t *node)
{
	size_t r = 0;

	while (h)
	{
		if (h == node)
			return (r);
		h = h->next;
		r++;
	}
	return (-1);
}
