#include "eshell.h"

/**
 * del_chain - test if current char in buffer is a chain delimeter
 * @f: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int del_chain(info_t *f, char *buff, size_t *ptr)
{
	size_t a = *ptr;

	if (buff[a] == '|' && buff[a + 1] == '|')
	{
		buff[a] = 0;
		a++;
		f->cmd_buff_type = CMD_OR;
	}
	else if (buff[a] == '&' && buff[a + 1] == '&')
	{
		buff[a] = 0;
		a++;
		f->cmd_buff_type = CMD_AND;
	}
	else if (buff[a] == ';')
	{
		buff[a] = 0;
		f->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = a;
	return (1);
}

/**
 * cont_chain - checks we should continue chaining based on last status
 * @f: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @a: starting position in buf
 * @l: length of buf
 *
 * Return: Void
 */
void cont_chain(info_t *f, char *buff, size_t *ptr, size_t a, size_t l)
{
	size_t b = *ptr;

	if (f->cmd_buff_type == CMD_AND)
	{
		if (f->ret_status)
		{
			buff[a] = 0;
			b = l;
		}
	}
	if (f->cmd_buff_type == CMD_OR)
	{
		if (!f->ret_status)
		{
			buff[a] = 0;
			b = l;
		}
	}

	*ptr = b;
}

/**
 * _alias - replaces an aliases in the tokenized string
 * @f: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _alias(info_t *f)
{
	int a;
	list_t *nd;
	char *pt;

	for (a = 0; a < 10; a++)
	{
		nd = find_Node(f->alias_nd, f->argv[0], '=');
		if (!nd)
			return (0);
		free(f->argv[0]);
		pt = _chrstr(nd->str, '=');
		if (!pt)
			return (0);
		pt = _dupstr(pt + 1);
		if (!pt)
			return (0);
		f->argv[0] = pt;
	}
	return (1);
}

/**
 * var_replace - replaces vars in the tokenized string
 * @f: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int var_replace(info_t *f)
{
	int a = 0;
	list_t *nd;

	for (a = 0; f->argv[a]; a++)
	{
		if (f->argv[a][0] != '$' || !f->argv[a][1])
			continue;

		if (!_cmpstr(f->argv[a], "$?"))
		{
			str_replace(&(f->argv[a]),
				_dupstr(convert_num(f->ret_status, 10, 0)));
			continue;
		}
		if (!_cmpstr(f->argv[a], "$$"))
		{
			str_replace(&(f->argv[a]),
				_dupstr(convert_num(getpid(), 10, 0)));
			continue;
		}
		nd = find_Node(f->list_env, &f->argv[a][1], '=');
		if (nd)
		{
			str_replace(&(f->argv[a]),
				_dupstr(_chrstr(nd->str, '=') + 1));
			continue;
		}
		str_replace(&f->argv[a], _dupstr(""));

	}
	return (0);
}

/**
 * str_replace - replaces string
 * @old_ptr: address of old string
 * @new_ptr: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int str_replace(char **old_ptr, char *new_ptr)
{
	free(*old_ptr);
	*old_ptr = new_ptr;
	return (1);
}
