#include "eshell.h"

/**
 * _chrstr - locates a character in a string
 * @str: the string to be parsed
 * @ch: the character to look for
 * Return: 0 for success
 */

size_t _chrstr(const char *str, char ch)
{
	size_t i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == ch)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
/**
 * _catnstr - concatenates two strings
 * @str_dest: the first string
 * @str_src: the second string
 * @a: the amount of bytes to be maximally used
 * Return: the concatenated string
 */

void _catnstr(char *str_dest, const char *str_src, size_t a)
{
	while (*str_dest != '\0')
	{
		str_dest++;
	}
	while (a > 0 && *str_src != '\0')
	{
		*str_dest++ = *str_src++;
		a--;
	}
	*str_dest = '\0';
}
/**
 * _cpynstr - copies a string
 * @str_dest: the destination string to be copied to
 * @str_src: the source string
 * @a: the amount of characters to be copied
 * Return: the concatenated string
 */
void _cpynstr(char *str_dest, const char *str_src, int a)
{
	int i;

	for (i = 0; i < a && str_src[i] != '\0'; i++)
	{
		str_dest[i] = str_src[i];
	}
	str_dest[i] = '\0';
}
