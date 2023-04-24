#include "eshell.h"

/**
 * count_Nodes - determines length of linked list
 * @head: pointer to first node
 * Return: length
 */
int count_Nodes(list_t *head)
{
	int count = 0;
	list_t *current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
/**
 * list_to_array - returns an array of strings of the list->str
 * @h_ref: pointer to first node
 * Return: array of strings
 */

char **list_to_array(list_t *h_ref)
{
	list_t *nd = h_ref;
	size_t ai = count_Nodes(h_ref), jb;
	char **sts;
	char *st;

	if (!h_ref || !ai)
		return (NULL);
	sts = malloc(sizeof(char *) * (ai + 1));
	if (!sts)
		return (NULL);
	for (ai = 0; nd; nd = nd->next, ai++)
	{
		st = malloc(_lenstr(nd->str) + 1);
		if (!st)
		{
			for (jb = 0; jb < ai; jb++)
				free(sts[jb]);
			free(sts);
			return (NULL);
		}

		st = _cpystr(st, nd->str);
		sts[ai] = st;
	}
	sts[ai] = NULL;
	return (sts);
}
/**
 * print_list_element - prints all elements of a list_t linked list
 * @h_ref: pointer to firstnode
 * Return: size of list
 */

size_t print_list_element(const list_t *h_ref)
{
	size_t ai = 0;

	while (h_ref)
	{
		_puts(convert_num(h_ref->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h_ref->str ? h_ref->str : "(nil)");
		_puts("\n");
		h_ref = h_ref->next;
		ai++;
	}
	return (ai);
}
/**
 * Node_Index - gets the index of a node
 * @h_ref: pointer to list head
 * @nd_ref: pointer to the node
 *
 * Return: index of node or -1
 */

int Node_Index(list_t *h_ref, list_t *nd_ref)
{
	int ai = 0;
	list_t *current_nd = h_ref;

	while (current_nd != NULL)
	{
		if (current_nd == nd_ref)
		{
			return (ai);
		}
		ai++;
		current_nd = current_nd->next;
	}
	return (-1); /* node not found in list */
}

/**
 * find_Node - returns node whose string starts with prefix
 * @nd: pointer to list head
 * @pref: string to match
 * @a: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *find_Node(list_t *nd, char *pref, char a)
{
	char *ph = NULL;

	while (nd)
	{
		*ph = starts_hay(nd->str, pref);
		if (ph && ((a == -1) || (*ph == a)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}
