#include "eshell.h"

/**
 * free_and_null - frees a pointer and NULLs the address
 * @pt: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_and_null(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
