#include "eshell.h"

/**
 * add_Node - adds a node to the start of the list
 * @h: pointer to the address of first node
 * @st: st field of node
 * @data: node index used by history
 * Return: the newnode
 */

list_t *add_Node(list_t **h, char *st, int data)
{
	list_t *new_h;

	if (!h)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	mem_set((void *)new_h, 0, sizeof(list_t));
	new_h->num= data;
	if (st)
	{
		new_h->str = _dupstr(st);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *h;
	*h = new_h;
	return (new_h);
}
/**
 * add_node_to_end - adds a node to the end of the list
 * @head_ref: address of pointer to head node
 * @data: node index used by history
 * @st: st field of node
 * Return: newnode
 */
list_t *add_node_to_end(list_t **head_ref, const char *st, int data)
{
	list_t *new_nd, *nd;

	if (!head_ref)
		return (NULL);

	nd = *head_ref;
	new_nd = malloc(sizeof(list_t));
	if (!new_nd)
		return (NULL);
	mem_set((void *)new_nd, 0, sizeof(list_t));
	new_nd->num = data;
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
		*head_ref = new_nd;
	return (new_nd);
}
/**
 * print_list_str - prints only the str element of a list_t linked list
 * @list: pointer to first node
 * Return:0 for success
 */

void print_list_str(list_t *list)
{
	list_t *curr = list;

	while (curr != NULL)
	{
		_puts(curr->str);
		curr = curr->next;
	}
}
/**
 * delete_node_at_index - deletes node at given index
 * @head_ref: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **head_ref, int index)
{
	if (*head_ref == NULL || index < 0)
	{
		return (0);
	}

	if (index == 0)
	{
		list_t *temp = *head_ref;

		*head_ref = temp->next;
		free(temp);
		return (1);
	}

	list_t *prev = NULL;
	list_t *curr = *head_ref;

	for (int i = 0; curr != NULL && i < index; i++)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
	{
		return (1);
	}
	prev->next = curr->next;
	free(curr);
}
/**
 * free_List - frees all nodes of a list
 * @h_ptr: address of pointer to head node
 *
 * Return:0 for success
 */
void free_List(list_t **h_ptr)
{
	list_t *current = *h_ptr;

	while (current != NULL)
	{
		list_t *next = current->next;
		free(current);
		current = next:
	}
	*h_ptr = NULL;
}
