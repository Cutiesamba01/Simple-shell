#include "shell.h"

/**
 * replace_alias - replaces aliases in tokenised string
 * @info: param struct
 *
 * Return: 1 if replacement occurred / 0 if otherwise
 */

int replace_alias(info_t *info)
{
	int r;
	list_t *node;
	char *p;

	for (r = 0; r < 10; r++)
	{
		node =  node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->s, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in tokenised string
 * @info: param struct
 *
 * Return: 1 if replacement occurred / 0 if otherwise
 */

int replace_vars(info_t *info)
{
	int h = 0;
	list_t *node;

	for (h = 0; info->argv[h]; h++)
	{
		if (info->argv[h][0] != '$' || !info->argv[h][1])
			continue;
		if (!_strcmp(info->argv[h], "$?"))
		{
			replace_string(&(info->argv[h]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[h], "$$"))
		{
			replace_string(&(info->argv[h]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[h][1], '=');
		if (node)
		{
			replace_string(&(info->argv[h]),
					_strdup(_strchr(node->s, '=') + 1));
			continue;
		}
		replace_string(&info->argv[h], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: old string adr
 * @new: new string(s)
 *
 * Return: 1 if replacement occurred / 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
		return (1);
}

/**
 * is_chain - tests if the current char in a buffer is a chain delimiter
 * @info: param struct
 * @buf: char buffer
 * @p: current position adr in buf
 *
 * Return: 1 if it is a chain delimiter / otherwise, 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t o = *p;

	if (buf[o] == '|' && buf[o + 1] == '|')
	{
		buf[o] = 0;
		o++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[o] == '&' && buf[o + 1] == '&')
	{
		buf[o] = 0;
		o++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[o] == ';')
	{
		buf[o] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = o;
	return (1);
}

/**
 * check_chain - checks if chaining should continue based on the last status
 * @info: param struct
 * @buf: char buffer
 * @p: current position adr in buf
 * @len: length of buf
 * @i: startimg position in buf
 *
 * Return: void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t d = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			d = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			d = len;
		}
	}
	*p = d;
}
