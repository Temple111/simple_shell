#include "shell.h"

/**
 * _lenstr - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: integer length of string
 */
int _lenstr(char *string)
{
	int ai = 0;

	if (!string)
		return (0);

	while (*string++)
		ai++;
	return (ai);
}

/**
 * _cmpstr - performs lexicogarphic comparison of two strangs.
 * @string1: the first strang
 * @string2: the second strang
 *
 * Return: negative if string1 < string2, positive if s1 > s2, zero if s1 == s2
 */
int _cmpstr(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * starts_hay - checks if needle starts with haystack
 * @hayst: string to search
 * @nee: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_hay(const char *hayst, const char *nee)
{
	while (*nee)
		if (*nee++ != *hayst++)
			return (NULL);
	return ((char *)hayst);
}

/**
 * _catstr - concatenates two strings
 * @dest_str: the destination buffer
 * @src_str: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_catstr(char *dest_str, char *src_str)
{
	char *rt = dest_str;

	while (*dest_str)
		dest_str++;
	while (*src_str)
		*dest_str++ = *src_str++;
	*dest_str = *src_str;
	return (rt);
}
