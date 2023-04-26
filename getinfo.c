#include "eshell.h"

/**
 * clear_info - initializes info_t struct
 * @f: struct address
 */
void clear_info(info_t *f)
{
	f->argu = NULL;
	f->argv = NULL;
	f->str_path = NULL;
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

	f->f_name = av[0];
	if (f->argu)
	{
		f->argv = towstr(f->argu, " \t");
		if (!f->argv)
		{

			f->argv = malloc(sizeof(char *) * 2);
			if (f->argv)
			{
				f->argv[0] = _dupstr(f->argu);
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
	f->str_path = NULL;
	if (every)
	{
		if (!f->cmd_buff)
			free(f->argu);
		if (f->list_env)
			free_list(&(f->list_env));
		if (f->hist_nd)
			free_list(&(f->hist_nd));
		if (f->alias_nd)
			free_list(&(f->alias_nd));
		free_string_array(f->cpy_env);
			f->cpy_env = NULL;
		free_and_null((void **)f->cmd_buff);
		if (f->read_fd > 2)
			close(f->read_fd);
		_putchar(BUFF_FLUSH);
	}
}
