#include "shell.h"

/**
 * _curr_env - prints the current environment
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _curr_env(info_t *f)
{
	print_list_str(f->env);
	return (0);
}

/**
 * _get_env - gets the value of an environ variable
 * @f: Structure containing potential arguments. Used to maintain
 * @varname: env var name
 *
 * Return: the value
 */
char *_get_env(info_t *f, const char *varname)
{
	list_t *nd = f->env;
	char *ph;

	while (nd)
	{
		ph = starts_hay(nd->str, varname);
		if (ph && *ph)
			return (ph);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *f)
{
	if (f->argc != 3)
	{
		_wputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(f, f->argv[1], f->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *f)
{
	int a;

	if (f->argc == 1)
	{
		_wputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= f->argc; a++)
		_unsetenv(f, f->argv[a]);

	return (0);
}

/**
 * populate_envlinked_list - populates env linked list
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_envlinked_list(info_t *f)
{
	list_t *nd = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_to_end(&nd, environ[a], 0);
	f->env = nd;
	return (0);
}
