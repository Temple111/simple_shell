#include "eshell.h"

/**
 * my_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_bk: byte size of previous block
 * @new_bk: byte size of new block
 *
 * Return: 0 for success
 */
void *my_realloc(void *ptr, size_t old_bk, size_t new_bk)
{
	if (new_bk == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		return (malloc(new_bk));
	}
	void *new_ptr = malloc(new_bk);

	if (new_ptr == NULL)
	{
		return (NULL);
	}
	size_t copy_size = old_bk < new_bk ? old_bk : new_bk;

	for (size_t j = 0; j < copy_size; j++)
	{
		((char *) new_ptr)[j] = ((char *) ptr)[j];
	}
	free(ptr);
	return (new_ptr);
}

/**
 ** mem_set - fills memory with a constant byte
 * @ptr: the pointer to the memory area
 * @val: the byte to fill *ptr with
 * @num: the amount of bytes to be filled
 * Return: 0 for success
 */
void *mem_set(void *ptr, int val, size_t num)
{
	unsigned char *p = ptr;

	for (size_t a = 0; a < num; a++)
	{
		*p++ = (unsigned char)val;
	}
	return (ptr);
}

/**
 * free_string_array - frees a string of strings
 * @string_array: string of strings
 * @num_strings: number of strings to be freed
 */

void free_string_array(char **string_array)
{
	int num_strings;

	for (int i = 0; i < num_strings; i++)
	{
		free(string_array[i]);
	}
	free(string_array);
}
