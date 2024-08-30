 #include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: potential args used in maintaining constant function prototype
 *
 *  Return: 0 if successful
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: param struct
 * @s: string alias
 *
 * Return: 0 if successful / 1 otherwise
 */

int unset_alias(info_t *info, char *s)
{
	char *p, r;
	int ret;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	r = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, s, -1)));
	*p = r;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: param struct
 * @s: the string alias
 *
 * Return: 0 if successful / 1 otherwise
 */

int set_alias(info_t *info, char *s)
{
	char *p;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, s));

	unset_alias(info, s);
	return (add_node_end(&(info->alias), s, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: 0 if successful / 1 otherwise
 */

int print_alias(list_t *node)
{
	char *p = NULL, *r = NULL;

	if (node)
	{
		p = _strchr(node->s, '=');
		for (r = node->s; r <= p; r++)
			_putchar(*r);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: potential args used in maintaining constant function prototype
 *
 * Return: 0 if successful
 */
int _myalias(info_t *info)
{
	int r = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (r = 1; info->argv[r]; r++)
	{
		p = _strchr(info->argv[r], '=');
		if (p)
			set_alias(info, info->argv[r]);
		else
			print_alias(node_starts_with(info->alias, info->argv[r], '='));
	}

	return (0);
}
