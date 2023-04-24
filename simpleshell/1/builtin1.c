#include "eshell.h"

/**
 * _disphist - displays the history list
 * @f: Structure containing potential arguments
 *  Return: Always 0
 */
int _disphist(info_t *f)
{
	print_list_element(f->history);
	return (0);
}

/**
 * alias_to_string - sets alias to string
 * @f: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_to_string(info_t *f, char *string)
{
	char *ph, ch;
	int rt;

	*ph = _chrstr(string, '=');
	if (!ph)
		return (1);
	ch = *ph;
	*ph = 0;
	rt = delete_node_at_index(&(f->alias),
		Node_Index(f->alias, find_Node(f->alias, string, -1)));
	*ph = ch;
	return (rt);
}

/**
 * alias_set - sets alias to string
 * @f: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info_t *f, char *string)
{
	char *ph;

	*ph = _chrstr(string, '=');
	if (!ph)
		return (1);
	if (!*++ph)
		return (alias_to_string(f, string));

	alias_to_string(f, string);
	return (add_node_to_end(&(f->alias), string, 0) == NULL);
}

/**
 * print_alias_string - prints an alias string
 * @nd: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_string(list_t *nd)
{
	char *ph = NULL, *b = NULL;

	if (nd)
	{
		*ph = _chrstr(nd->str, '=');
		for (b = nd->str; b <= ph; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(ph + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias_mimic - mimics the alias builtin (man alias)
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _alias_mimic(info_t *f)
{
	int a = 0;
	char *ph = NULL;
	list_t *nd = NULL;

	if (f->argc == 1)
	{
		nd = f->alias;
		while (nd)
		{
			print_alias_string(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (a = 1; f->argv[a]; a++)
	{
		*ph = _chrstr(f->argv[a], '=');
		if (ph)
			alias_set(f, f->argv[a]);
		else
			print_alias_string(find_Node(f->alias, f->argv[a], '='));
	}

	return (0);
}
