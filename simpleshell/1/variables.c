#include "eshell.h"

/**
 * del_chain - checks if char in buffer is a chain delimeter
 * @f: the parameter struct
 * @bf: the char buffer
 * @ps: address of current position in buffer
 *
 * Return: 0 for success
 */
int del_chain(info_t *f, char *bf, size_t *ps)
{
	size_t i = *ps;

	if (bf[i] == '|' && bf[i + 1] == '|')
	{
		bf[i] = 0;
		i++;
		f->cmd_buf_type = CMD_OR;
	}
	else if (bf[i] == '&' && bf[i + 1] == '&')
	{
		bf[i] = 0;
		i++;
		f->cmd_buf_type = CMD_AND;
	}
	else if (bf[i] == ';')
	{
		bf[i] = 0;
		f->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ps = i;
	return (1);
}

/**
 * cont_chain - tests if chaining should continue based on last status
 * @f: the parameter struct
 * @bf: the char buffer
 * @ps: address of current position in buffer
 * @s: starting position in buf
 * @l: length of buffer
 *
 * Return: 0 for success
 */
void cont_chain(info_t *f, char *bf, size_t *ps, size_t s, size_t l)
{
	size_t i = *ps;

	if (f->cmd_buf_type == CMD_AND)
	{
		if (f->status)
		{
			bf[s] = 0;
			i = l;
		}
	}
	if (f->cmd_buf_type == CMD_OR)
	{
		if (!f->status)
		{
			bf[s] = 0;
			i = l;
		}
	}

	*ps = i;
}

/**
 * _alias - replaces alias in tokenized string
 * @f: the parameter struct
 * Return: 0 for success
 */
int _alias(info_t *f)
{
	int j;
	list_t *nd;
	char *ps;

	for (j = 0; j < 10; j++)
	{
		nd = find_Node(f->alias, f->argv[0], '=');
		if (!nd)
			return (0);
		free(f->argv[0]);
		*ps = _chrstr(nd->str, '=');
		if (!ps)
			return (0);
		ps = _dupstr(ps + 1);
		if (!ps)
			return (0);
		f->argv[0] = ps;
	}
	return (1);
}

/**
 * var_replace - changes variables in the tokenized string
 * @f: the parameter struct
 * Return: 0 for success
 */
int var_replace(info_t *f)
{
	int j = 0;
	list_t *nd;

	for (j = 0; f->argv[j]; j++)
	{
		if (f->argv[j][0] != '$' || !f->argv[j][1])
			continue;

		if (!_cmpstr(f->argv[j], "$?"))
		{
			str_replace(&(f->argv[j]),
					_dupstr(convert_num(f->status, 10, 0)));
			continue;
		}
		if (!_cmpstr(f->argv[j], "$$"))
		{
			str_replace(&(f->argv[j]),
					_dupstr(convert_num(getpid(), 10, 0)));
			continue;
		}
		nd = find_Node(f->env, &f->argv[j][1], '=');
		if (nd)
		{
			str_replace(&(f->argv[j]),
					_dupstr(_chrstr(nd->str, '=') + 1));
			continue;
		}
		str_replace(&f->argv[j], _dupstr(""));

	}
	return (0);
}

/**
 * str_replace - replaces string
 * @d: pointer to address of last string
 * @n: first string
 * Return: 0 if successful
 */
int str_replace(char **d, char *n)
{
	free(*d);
	*d = n;
	return (1);
}
