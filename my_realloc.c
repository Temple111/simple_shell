#include "eshell.h"

/**
 **mem_set - fills memory with a constant byte
 *@ma: the pointer to the memory area
 *@byte: the byte to fill *s with
 *@num: the amount of bytes to be filled
 *Return: (ma) a pointer to the memory area s
 */
char *mem_set(char *ma, char byte, unsigned int num)
{
	unsigned int a;

	for (a = 0; a < num; a++)
		ma[a] = byte;
	return (ma);
}

/**
 * free_string_array - frees a string of strings
 * @arr: string of strings
 */
void free_string_array(char **arr)
{
	char **b = arr;

	if (!arr)
		return;
	while (*arr)
		free(*arr++);
	free(b);
}

/**
 * my_realloc - reallocates a block of memory
 * @pt: pointer to previous malloc'ated block
 * @old_byte: byte size of previous block
 * @new_byte: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *my_realloc(void *pt, unsigned int old_byte, unsigned int new_byte)
{
	char *ps;

	if (!pt)
		return (malloc(new_byte));
	if (!new_byte)
		return (free(pt), NULL);
	if (new_byte == old_byte)
		return (pt);

	ps = malloc(new_byte);
	if (!ps)
		return (NULL);

	old_byte = old_byte < new_byte ? old_byte : new_byte;
	while (old_byte--)
		ps[old_byte] = ((char *)pt)[old_byte];
	free(pt);
	return (ps);
}
