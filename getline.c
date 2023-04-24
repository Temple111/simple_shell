#include "shell.h"

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
	ssize_t rd = 0;
	size_t len_ph = 0;

	if (!*l) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rd = getline(buff, &len_ph, stdin);
#else
		rd = _getline(f, buff, &len_ph);
#endif
		if (rd > 0)
		{
			if ((*buff)[rd - 1] == '\n')
			{
				(*buff)[rd - 1] = '\0'; /* remove trailing newline */
				rd--;
			}
			f->linecount_flag = 1;
			replace_hash(*buff);
			build_hist_linkedlist(f, *buff, f->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*l = rd;
				f->cmd_buf = buff;
			}
		}
	}
	return (rd);
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
	ssize_t rd = 0;
	char **buf_ph = &(f->arg), *ph;

	_putchar(BUF_FLUSH);
	rd = input_buff(f, &buff, &l);
	if (rd == -1) /* EOF */
		return (-1);
	if (l)	/* we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		ph = buff + a; /* get pointer for return */

		cont_chain(f, buff, &b, a, l);
		while (b < l) /* iterate to semicolon or end */
		{
			if (del_chain(f, buff, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= l) /* reached end of buffer? */
		{
			a = l = 0; /* reset position and length */
			f->cmd_buf_type = CMD_NORM;
		}

		*buf_ph = ph; /* pass back pointer to current command position */
		return (_lenstr(ph)); /* return length of current command */
	}

	*buf_ph = buff; /* else not a chain, pass back buffer from _getline() */
	return (rd); /* return length of buffer from _getline() */
}

/**
 * read_buff - reads a buffer
 * @f: parameter struct
 * @buff: buffer
 * @a: size
 *
 * Return: r
 */
ssize_t read_buff(info_t *f, char *buff, size_t *a)
{
	ssize_t rd = 0;

	if (*a)
		return (0);
	rd = read(f->readfd, buff, READ_BUF_SIZE);
	if (rd >= 0)
		*a = rd;
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
	size_t k;
	ssize_t rd = 0, s = 0;
	char *ph = NULL, *new_ph = NULL, *ch;

	ph = *pt;
	if (ph && l)
		s = *l;
	if (a == len)
		a = len = 0;

	rd = read_buff(f, buff, &len);
	if (rd == -1 || (rd == 0 && len == 0))
		return (-1);

	ch = _chrstr(buff + a, '\n');
	k = ch ? 1 + (unsigned int)(ch - buff) : len;
	new_ph = my_realloc(ph, s, s ? s + k : k + 1);
	if (!new_ph) /* MALLOC FAILURE! */
		return (ph ? free(ph), -1 : -1);

	if (s)
		_catnstr(new_ph, buff + a, k - a);
	else
		_cpynstr(new_ph, buff + a, k - a + 1);

	s += k - a;
	a = k;
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
