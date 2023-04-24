#include "shell.h"

/**
 **_cpynstr - copies a string
 *@str_dest: the destination string to be copied to
 *@str_src: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_cpynstr(char *str_dest, char *str_src, int num)
{
	int a, b;
	char *sh = str_dest;

	a = 0;
	while (str_src[a] != '\0' && a < num - 1)
	{
		str_dest[a] = str_src[a];
		a++;
	}
	if (a < num)
	{
		b = a;
		while (b < num)
		{
			str_dest[b] = '\0';
			b++;
		}
	}
	return (sh);
}

/**
 **_catnstr - concatenates two strings
 *@dest_str: the first string
 *@src_str: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_catnstr(char *dest_str, char *src_str, int num)
{
	int a, b;
	char *sh = dest_str;

	a = 0;
	b = 0;
	while (dest_str[a] != '\0')
		a++;
	while (src_str[b] != '\0' && b < num)
	{
		dest_str[a] = src_str[b];
		a++;
		b++;
	}
	if (b < num)
		dest_str[a] = '\0';
	return (sh);
}

/**
 **_chrstr - locates a character in a string
 *@st: the string to be parsed
 *@ch: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_chrstr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
