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
	ssize_t rd = 0;
	size_t len_ph = 0;

	if (!*l)
	{
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
				(*buff)[rd - 1] = '\0';
				rd--;
			}
			f->lineinput_count = 1;
			replace_hash(*buff);
			build_hist_linkedlist(f, *buff, f->hist_count++);
			{
				*l = rd;
				f->cmd_buff = buff;
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
	static char *buff;
	static size_t a, b, l;
	ssize_t rd = 0;
	char **buff_ph = &(f->argu), *ph;

	_putchar(BUFF_FLUSH);
	rd = input_buff(f, &buff, &l);
	if (rd == -1) /* EOF */
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
			f->cmd_buff_type = CMD_NORM;
		}

		*buff_ph = ph;
		return (_lenstr(ph));
	}

	*buff_ph = buff;
	return (rd);
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
	rd = read(f->read_fd, buff, READ_BUFF_SIZE);
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
	static char buff[READ_BUFF_SIZE];
	static size_t a, len;
	size_t d;
	ssize_t rd = 0, sh = 0;
	char *ph = NULL, *new_ph = NULL, *ch;

	ph = *pt;
	if (ph && l)
		sh = *l;
	if (a == len)
		a = len = 0;

	rd = read_buff(f, buff, &len);
	if (rd == -1 || (rd == 0 && len == 0))
		return (-1);

	ch = _chrstr(buff + a, '\n');
	d = ch ? 1 + (unsigned int)(ch - buff) : len;
	new_ph = my_realloc(ph, sh, sh ? sh + d : d + 1);
	if (!new_ph) /* MALLOC FAILURE! */
		return (ph ? free(ph), -1 : -1);

	if (sh)
		_catnstr(new_ph, buff + a, d - a);
	else
		_cpynstr(new_ph, buff + a, d - a + 1);

	sh += d - a;
	a = d;
	ph = new_ph;

	if (l)
		*l = sh;
	*pt = ph;
	return (sh);
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
	_putchar(BUFF_FLUSH);
}
