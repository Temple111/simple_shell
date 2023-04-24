#include "eshell.h"

/**
 * hist_file - gets the history file
 * @f: parameter struct
 *
 * Return: 0 on success
 */

char *hist_file(info_t *f)
{
	char *buff, *directory;

	directory = _get_env(f, "HOME=");
	if (!directory)
		return (NULL);
	buff = malloc(sizeof(char) * (_lenstr(directory) + _lenstr(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_cpystr(buff, directory);
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
	ssize_t op;
	char *file = hist_file(f);
	list_t *nd = NULL;

	if (!file)
		return (-1);

	op = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (op == -1)
		return (-1);
	for (nd = f->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, op);
		_putfd('\n', op);
	}
	_putfd(BUF_FLUSH, op);
	close(op);
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
	int a, end = 0, lcount = 0;
	ssize_t op, rd, fsize = 0;
	struct stat st;
	char *buff = NULL, *file = hist_file(f);

	if (!file)
		return (0);

	op = open(file, O_RDONLY);
	free(file);
	if (op == -1)
		return (0);
	if (!fstat(op, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rd = read(op, buff, fsize);
	buff[fsize] = 0;
	if (rd <= 0)
		return (free(buff), 0);
	close(op);
	for (a = 0; a < fsize; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			build_hist_linkedlist(f, buff + end, lcount++);
			end = a + 1;
		}
	if (end != a)
		build_hist_linkedlist(f, buff + end, lcount++);
	free(buff);
	f->histcount = lcount;
	while (f->histcount-- >= HIST_MAX)
		delete_node_at_index(&(f->history), 0);
	renumb_hist(f);
	return (f->histcount);
}

/**
 * build_hist_linkedlist - adds entry to a history linked list
 * @f: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @lcount: the history linecount, histcount
 *
 * Return: 0 for success
 */
int build_hist_linkedlist(info_t *f, char *buff, int lcount)
{
	list_t *nd = NULL;

	if (f->history)
		nd = f->history;
	add_node_to_end(&nd, buff, lcount);

	if (!f->history)
		f->history = nd;
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
	list_t *nd = f->history;
	int a = 0;

	while (nd)
	{
		nd->num = a++;
		nd = nd->next;
	}
	return (f->histcount = a);
}

