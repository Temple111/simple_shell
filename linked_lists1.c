#include "shell.h"

/**
 * count_Nodes - determines length of linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t count_Nodes(const list_t *hd)
{
	size_t a = 0;

	while (hd)
	{
		hd = hd->next;
		a++;
	}
	return (a);
}

/**
 * list_to_array - returns an array of strings of the list->str
 * @hd: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_array(list_t *hd)
{
	list_t *nd = hd;
	size_t a = count_Nodes(hd), b;
	char **sts;
	char *st;

	if (!hd || !a)
		return (NULL);
	sts = malloc(sizeof(char *) * (a + 1));
	if (!sts)
		return (NULL);
	for (a = 0; nd; nd = nd->next, a++)
	{
		st = malloc(_lenstr(nd->str) + 1);
		if (!st)
		{
			for (b = 0; b < a; b++)
				free(sts[b]);
			free(sts);
			return (NULL);
		}

		st = _cpystr(st, nd->str);
		sts[a] = st;
	}
	sts[a] = NULL;
	return (sts);
}


/**
 * print_list_element - prints all elements of a list_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_element(const list_t *hd)
{
	size_t a = 0;

	while (hd)
	{
		_puts(convert_num(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		a++;
	}
	return (a);
}

/**
 * find_Node - returns node whose string starts with prefix
 * @nd: pointer to list head
 * @pref: string to match
 * @z: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *find_Node(list_t *nd, char *pref, char z)
{
	char *ph = NULL;

	while (nd)
	{
		ph = starts_hay(nd->str, pref);
		if (ph && ((z == -1) || (*ph == z)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * Node_Index - gets the index of a node
 * @hd: pointer to list head
 * @nd: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t Node_Index(list_t *hd, list_t *nd)
{
	size_t ai = 0;

	while (hd)
	{
		if (hd == nd)
			return (ai);
		hd = hd->next;
		ai++;
	}
	return (-1);
}
