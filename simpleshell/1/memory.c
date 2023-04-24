#include "eshell.h"

/**
 * free_and_null - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */
void free_and_null(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
