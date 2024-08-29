#include "shell.h"

/**
 * build_history_list - builds the hisotyr of a linked list
 * @info: potential args used in maintaining constant function prototype
 * @buf: buffer
 * @linecount: history line count (histcount)
 *
 * Return: 0 if successful
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * get_history_file - gets history file(s)
 * @info: param struct
 *
 * Return: string containing the history file(s)
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates history file / appends to the existing one
 * @info: param struct
 *
 * Return: 0 if successful / 1 otherwise
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->s, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (0);
}

/**
 * read_history - reads file containg history
 * @info: param struct
 *
 * Return: histcount if successful / 1 otherwise
 */

int read_history(info_t *info)
{
	int r, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (1);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (1);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (1);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (1);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (r = 0; r < fsize; r++)
		if (buf[r] == '\n')
		{
			buf[r] = 0;
			build_history_list(info, buf + last, linecount++);
			last = r + 1;
		}
	if (last != r)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * renumber_history - renumbers the history linked list after any change occurs
 * @info: potential args used in maintaining constant function prototype
 *
 * Return: renumbered history count (histcount)
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int h = 0;

	while (node)
	{
		node->num = h++;
		node = node->next;
	}
	return (info->histcount = h);
}
