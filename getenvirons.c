#include "shell.h"

/**
 * get_env - returns the string array copy of our environ
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_env(info_t *f)
{
	if (!f->environ || f->env_changed)
	{
		f->environ = list_to_array(f->env);
		f->env_changed = 0;
	}

	return (f->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @val: the string env var property
 */
int _unsetenv(info_t *f, char *val)
{
	list_t *nd = f->env;
	size_t a = 0;
	char *ph;

	if (!nd || !val)
		return (0);

	while (nd)
	{
		ph = starts_hay(nd->str, val);
		if (ph && *ph == '=')
		{
			f->env_changed = delete_node_at_index(&(f->env), a);
			a = 0;
			nd = f->env;
			continue;
		}
		nd = nd->next;
		a++;
	}
	return (f->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @va: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *f, char *va, char *val)
{
	char *buff = NULL;
	list_t *nd;
	char *ph;

	if (!va || !val)
		return (0);

	buff = malloc(_lenstr(va) + _lenstr(val) + 2);
	if (!buff)
		return (1);
	_cpystr(buff, va);
	_catstr(buff, "=");
	_catstr(buff, val);
	nd = f->env;
	while (nd)
	{
		ph = starts_hay(nd->str, va);
		if (ph && *ph == '=')
		{
			free(nd->str);
			nd->str = buff;
			f->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	add_node_to_end(&(f->env), buff, 0);
	free(buff);
	f->env_changed = 1;
	return (0);
}
