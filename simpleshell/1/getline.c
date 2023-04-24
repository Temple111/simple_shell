#include "eshell.h"

/**
 * input_buff - buffers chained commands
 * @f: parameter struct
 * @buff: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *f, char **buff, size_t *l)
{
	ssize_t a = 0;
	size_t len_p = 0;

	if (!*l)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buff, &len_p, stdin);
#else
		a = _getline(f, buff, &len_p);
#endif
		if (a > 0)
		{
			if ((*buff)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0';
				a--;
			}
			f->linecount_flag = 1;
			replace_hash(*buff);
			build_hist_linkedlist(f, *buff, f->histcount++);
			/* if (_chrstr(*buf, ';')) is this a command chain? */
			{
				*l = a;
				f->cmd_buf = buff;
			}
		}
	}
	return (a);
}

/**
 * get_input - gets a line minus the newline
 * @f: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *f)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t a, b, l;
	ssize_t c = 0;
	char **buf_ph = &(f->arg), *ph;

	_putchar(BUF_FLUSH);
	c = input_buff(f, &buff, &l);
	if (c == -1) /* EOF */
		return (-1);
	if (l)
	{
		b = a;
		ph = buff + a;

		cont_chain(f, buff, &b, a, l);
		while (b < l)
		{
			if (del_chain(f, buff, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= l)
		{
			a = l = 0;
			f->cmd_buf_type = CMD_NORM;
		}

		*buf_ph = ph;
		return (_lenstr(ph));
	}

	*buf_ph = buff;
	return (c);
}

/**
 * read_buff - reads a buffer
 * @f: parameter struct
 * @buff: buffer
 * @j: size
 *
 * Return: rd
 */
ssize_t read_buff(info_t *f, char *buff, size_t *j)
{
	ssize_t rd = 0;

	if (*j)
		return (0);
	rd = read(f->readfd, buff, READ_BUF_SIZE);
	if (rd >= 0)
		*j = rd;
	return (rd);
}

/**
 * _getline - gets the next line of input from STDIN
 * @f: parameter struct
 * @pt: address of pointer to buffer, preallocated or NULL
 * @l: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *f, char **pt, size_t *l)
{
	static char buff[READ_BUF_SIZE];
	static size_t a, len;
	size_t b;
	ssize_t rd = 0, s = 0;
	char *ph = NULL, *new_ph = NULL, *c;

	ph = *pt;
	if (ph && l)
		s = *l;
	if (a == len)
		a = len = 0;

	rd = read_buff(f, buff, &len);
	if (rd == -1 || (rd == 0 && len == 0))
		return (-1);

	*c = _chrstr(buff + a, '\n');
	b = c ? 1 + (unsigned int)(c - buff) : len;
	new_ph = my_realloc(ph, s, s ? s + b : b + 1);
	if (!new_ph) /* MALLOC FAILURE! */
		return (ph ? free(ph), -1 : -1);

	if (s)
		_catnstr(new_ph, buff + a, b - a);
	else
		_cpynstr(new_ph, buff + a, b - a + 1);

	s += b - a;
	a = b;
	ph = new_ph;

	if (l)
		*l = s;
	*pt = ph;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

