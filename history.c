#include "eshell.h"

/**
 * get_hist_file - gets the history file
 * @f: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(info_t *f)
{
	char *buff, *dr;

	dr = _get_env(f, "HOME=");
	if (!dr)
		return (NULL);
	buff = malloc(sizeof(char) * (_lenstr(dr) + _lenstr(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_cpystr(buff, dr);
	_catstr(buff, "/");
	_catstr(buff, HIST_FILE);
	return (buff);
}

/**
 * write_hist - creates a file, or appends to an existing file
 * @f: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_t *f)
{
	ssize_t pn;
	char *file_n = get_hist_file(f);
	list_t *nd = NULL;

	if (!file_n)
		return (-1);

	pn = open(file_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_n);
	if (pn == -1)
		return (-1);
	for (nd = f->hist_nd; nd; nd = nd->next)
	{
		_putsfd(nd->str, pn);
		_putfd('\n', pn);
	}
	_putfd(BUFF_FLUSH, pn);
	close(pn);
	return (1);
}

/**
 * read_hist - reads history from file
 * @f: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(info_t *f)
{
	int a, end = 0, l_count = 0;
	ssize_t op, rd, f_size = 0;
	struct stat st;
	char *buff = NULL, *file_n = get_hist_file(f);

	if (!file_n)
		return (0);

	op = open(file_n, O_RDONLY);
	free(file_n);
	if (op == -1)
		return (0);
	if (!fstat(op, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	rd = read(op, buff, f_size);
	buff[f_size] = 0;
	if (rd <= 0)
		return (free(buff), 0);
	close(op);
	for (a = 0; a < f_size; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			build_hist_linkedlist(f, buff + end, l_count++);
			end = a + 1;
		}
	if (end != a)
		build_hist_linkedlist(f, buff + end, l_count++);
	free(buff);
	f->hist_count = l_count;
	while (f->hist_count-- >= HIST_MAX)
		delete_node_at_index(&(f->hist_nd), 0);
	renumb_hist(f);
	return (f->hist_count);
}

/**
 * build_hist_linkedlist - adds entry to a history linked list
 * @f: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @l_count: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_linkedlist(info_t *f, char *buff, int l_count)
{
	list_t *nd = NULL;

	if (f->hist_nd)
		nd = f->hist_nd;
	add_node_to_end(&nd, buff, l_count);

	if (!f->hist_nd)
		f->hist_nd = nd;
	return (0);
}

/**
 * renumb_hist - renumbers the history linked list after changes
 * @f: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumb_hist(info_t *f)
{
	list_t *nd = f->hist_nd;
	int a = 0;

	while (nd)
	{
		nd->data = a++;
		nd = nd->next;
	}
	return (f->hist_count = a);
}
