#include "eshell.h"

/**
 * _cpystr- copies a given string
 * @dest_str: where string is copied to
 * @src_str: where string is copied from
 * Return: 0 for success
 */

char *_cpystr(char *dest_str, const char *src_str)
{
	while (*src_str)
	{
		*dest_str = *src_str;
		src_str++;
		dest_str++;
	}
	*dest_str = '\0';
}

/**
 * _dupstr - duplicates a string
 * @ori_str: string to duplicate
 *
 * Return: 0 for success
 */

char *_dupstr(const char ori_str[])
{
	char *dup;
	int len = 0, j = 0;

	while (ori_str[len] != '\0')
	{
		len++;
	}
	dup = (char *) malloc(len * sizeof(char));
	while (ori_str[j] != '\0')
	{
		dup[j] = ori_str[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}
/**
 * _puts - prints an input string
 * @st: the string to be printed
 * Return: 0 for success
 */
void _puts(char st[])
{
	int a = 0;

	while (st[a] != '\0')
	{
		_putchar(st[a]);
		a++;
	}
}

/**
 * _putchar - writes a character to stdout
 * @ch: The character to print
 *
 * Return: 0 on success
 */
int _putchar(char ch)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[j++] = ch;
	return (1);
}

