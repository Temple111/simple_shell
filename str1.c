#include "eshell.h"

/**
 * _cpystr - copies a string
 * @dest_str: the destination
 * @src_str: the source
 *
 * Return: pointer to destination
 */
char *_cpystr(char *dest_str, char *src_str)
{
	int a = 0;

	if (dest_str == src_str || src_str == 0)
		return (dest_str);
	while (src_str[a])
	{
		dest_str[a] = src_str[a];
		a++;
	}
	dest_str[a] = 0;
	return (dest_str);
}

/**
 * _dupstr - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_dupstr(const char *string)
{
	int l = 0;
	char *rt;

	if (string == NULL)
		return (NULL);
	while (*string++)
		l++;
	rt = malloc(sizeof(char) * (l + 1));
	if (!rt)
		return (NULL);
	for (l++; l--;)
		rt[l] = *--string;
	return (rt);
}

/**
 *_puts - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
	int a = 0;

	if (!string)
		return;
	while (string[a] != '\0')
	{
		_putchar(string[a]);
		a++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int ai;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || ai >= WRITE_BUFF_SIZE)
	{
		write(1, buff, ai);
		ai = 0;
	}
	if (ch != BUFF_FLUSH)

		buff[ai++] = ch;
	return (1);
}
