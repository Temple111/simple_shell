#include "eshell.h"

/**
 * _lenstr - returns the length of a string
 * @st: the string whose length to check
 * Return: 0 for success
 */

int _lenstr(char st[])
{
	int l = 0;

	while (st[l] != '\0')
	{
		l++;
	}
	return (l);
}
/**
 * _cmpstr - performs lexicogarphic comparison of two strangs.
 * @st1: string 1
 * @st2: string 2
 * Return: 0 for success
 */

int _cmpstr(char *st1, char *st2)
{
	int a = 0;

	while (st1[a] != '\0' && st2[a] != '\0')
	{
		if (st1[a] < st2[a])
		{
			return (-1);
		}
	else if (st1[a] > st2[a])
	{
		return (1);
	}
	a++;
	}
	if (st1[a] == '\0' && st2[a] == '\0')
	{
		return (0);
	}
	else if (st1[a] == '\0')
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}

/**
 * _catstr - concatenates two strings
 * @st1: the destination buffer
 * @st2: string to joined to st1
 *
 * Return: 0 success
 */
void _catstr(char st1[], char st2[])
{
	int a = 0, b = 0;

	while (st1[a] != '\0')
	{
		a++;
	}
	while (st2[b] != '\0')
	{
		st1[a] = st2[b];
		a++;
		b++;
	}
	st1[a] = '\0';
}
/**
 * starts_hay - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: 0 good
 */
char starts_hay(const char *haystack,const char *needle)
{
	while (*needle != '\0')
	{
		if (*haystack == '\0' || *haystack != *needle)
	{
		return (0);
	}
		haystack++;
		needle++;
	}
	return (1);
}
