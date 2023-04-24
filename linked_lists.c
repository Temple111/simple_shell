#include "shell.h"

/**
 * add_Node - adds a node to the start of the list
 * @hd: address of pointer to head node
 * @st: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *add_Node(list_t **hd, const char *st, int number)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	mem_set((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = number;
	if (st)
	{
		new_hd->str = _dupstr(st);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * add_node_to_end - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @st: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_to_end(list_t **hd, const char *st, int number)
{
	list_t *new_nd, *nd;

	if (!hd)
		return (NULL);

	nd = *hd;
	new_nd = malloc(sizeof(list_t));
	if (!new_nd)
		return (NULL);
	mem_set((void *)new_nd, 0, sizeof(list_t));
	new_nd->num = number;
	if (st)
	{
		new_nd->str = _dupstr(st);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = new_nd;
	}
	else
		*hd = new_nd;
	return (new_nd);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *hd)
{
	size_t a = 0;

	while (hd)
	{
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - deletes node at given index
 * @hd: address of pointer to first node
 * @idx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **hd, unsigned int idx)
{
	list_t *nd, *pre_nd;
	unsigned int a = 0;

	if (!hd || !*hd)
		return (0);

	if (!idx)
	{
		nd = *hd;
		*hd = (*hd)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *hd;
	while (nd)
	{
		if (a == idx)
		{
			pre_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		a++;
		pre_nd = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @hd_pt: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **hd_pt)
{
	list_t *nd, *next_nd, *hd;

	if (!hd_pt || !*hd_pt)
		return;
	hd = *hd_pt;
	nd = hd;
	while (nd)
	{
		next_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = next_nd;
	}
	*hd_pt = NULL;
}
