#include "shell.h"

/**
 * _getenv - gets an environ variable value
 * @info: potential args used in maintaining constant function prototype
 * @name: name of the environ variable
 *
 * Return: the value of the environ variable
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->s, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialise a new env variable / modify one which exists
 * @info: potential args used in maintaining constant function prototype
 *
 * Return: 0 if successful
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of args\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - removes an env variable
 * @info: potential args used in maintaining constant function prototype
 *
 * Return: 0 if successful
 */

int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few args\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);
	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: potential args used in maintaining constant function prototype
 *
 * Return: 0 if successful
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t d;

	for (d = 0; environ[d]; d++)
		add_node_end(&node, environ[d], 0);
	info->env = node;
	return (0);
}

/**
 * _myenv - prints current env
 * @info: potential args used in maintaining constant function prototype
 *
 * Return: 0 if successful
 */

int _myenv(info_t *info)
{
	print_list(info->env);
	return (0);
}
