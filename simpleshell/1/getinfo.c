#include "eshell.h"

/**
 * clear_info - initializes info_t struct
 * @f: struct address
 */
void clear_info(info_t *f)
{
	f->arg = NULL;
	f->argv = NULL;
	f->path = NULL;
	f->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @f: struct address
 * @av: argument vector
 */
void set_info(info_t *f, char **av)
{
	int a = 0;

	f->fname = av[0];
	if (f->arg)
	{
		f->argv = towstr(f->arg, " \t");
		if (!f->argv)
		{

			f->argv = malloc(sizeof(char *) * 2);
			if (f->argv)
			{
				f->argv[0] = _dupstr(f->arg);
				f->argv[1] = NULL;
			}
		}
		for (a = 0; f->argv && f->argv[a]; a++)
			;
		f->argc = a;

		_alias(f);
		var_replace(f);
	}
}

/**
 * free_info - frees info_t struct fields
 * @f: struct address
 * @every: true if freeing all fields
 */
void free_info(info_t *f, int every)
{
	free_string_array(f->argv);
	f->argv = NULL;
	f->path = NULL;
	if (every)
	{
		if (!f->cmd_buf)
			free(f->arg);
		if (f->env)
			free_List(&(f->env));
		if (f->history)
			free_List(&(f->history));
		if (f->alias)
			free_List(&(f->alias));
		free_string_array(f->environ);
			f->environ = NULL;
		free_and_null((void **)f->cmd_buf);
		if (f->readfd > 2)
			close(f->readfd);
		_putchar(BUF_FLUSH);
	}
}
