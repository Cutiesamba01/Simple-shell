#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: param struct
 * @buf: buffer adr
 * @len: len var adr
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t h = 0;
	size_t len_p = 0;

	if (!len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
	#if USE_GETLINE
		h = getline(buf, &len_p, stdin);
	#else
		h = _getline(info, buf, &len_p);
	#endif
		if (h > 0)
		{
			if ((*buf)[h - 1] == '\n')
			{
				(*buf)[h - 1] = '\0';
				h--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = h;
				info->cmd_buf = buf;
			}
		}
	}
	return (h);
}

/**
 * get_input -  gets a line
 * @info: param struct
 *
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t r, s, len;
	ssize_t h = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	h = input_buf(info, &buf, &len);
	if (h == -1)
		return (-1);
	if (len)
	{
		s = r;
		p = buf + r;

		check_chain(info, buf, &s, r, len);
		while (s < len)
		{
			if (is_chain(info, buf, &s))
				break;
			s++;
		}

		r = s + 1;
		if (r >= len)
		{
			r = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (h);
}

/**
 * read_buf - reads buffer
 * @info: param struct
 * @buf: buffer
 * @a: size
 *
 * Return: h
 */

ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
	ssize_t h = 0;

	if (*a)
		return (0);
	h = read(info->readfd, buf, READ_BUF_SIZE);
	if (h >= 0)
		*a = h;
	return (h);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: param struct
 * @ptr: buffer pointer adr ( preallocated / NULL)
 * @length: size of preallocated / NULL ptr buffer
 *
 * Return: m
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t k;
	ssize_t l = 0, m = 0;
	char *p = NULL, *new_p = NULL, *e;

	p = *ptr;
	if (p && length)
		m = *length;
	if (j == len)
		j = len = 0;
	l = read_buf(info, buf, &len);
	if (l == -1 || (l == 0 && len == 0))
		return (-1);
	e = _strchr(buf + j, '\n');
	k = e ? 1 + (unsigned int)(e - buf) : len;
	new_p = _realloc(p, m, m ? m + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (m)
		_strncat(new_p, buf + j, k - j);
	else
		_strncpy(new_p, buf + j, k - j + 1);
	m += k - j;
	j = k;
	p = new_p;
	if (length)
		*length = m;
	*ptr = p;
	return (m);
}

/**
 * sigintHandler - handles block ctrl^C
 * @sig_num: signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$");
	_putchar(BUF_FLUSH);
}
