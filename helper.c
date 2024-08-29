#include "shell.h"

/**
 * is_cmd - determines if a file is executable
 * @info: info struct
 * @path: path to the file
 *
 * Return: 1 if true / 0 otherwise
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates chars
 * @paths: the PATH string
 * @start: starts the index
 * @stop: stops the index
 *
 * Return: pointer to the new buffer
 */

char *dup_chars(char *paths, int start, int stop)
{
	static char buf[1024];
	int c = 0, s = 0;

	for (s = 0, c = start; c < stop; c++)
		if (paths[c] != ':')
			buf[s++] = paths[c];
	buf[s] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: info struct
 * @paths: the PATH string
 * @cmd: the cmd to be found
 *
 * Return: full path of cmd if found / NULL
 */

char *find_path(info_t *info, char *paths, char *cmd)
{
	int r = 0, curr_pos = 0;
	char *path;

	if (!paths)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!paths[r] || paths[r] == ':')
		{
			path = dup_chars(paths, curr_pos, r);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!paths[r])
				break;
			curr_pos = r;
		}
		r++;
	}
	return (NULL);
}
