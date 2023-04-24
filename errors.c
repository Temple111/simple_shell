#include "shell.h"

/**
 *_wputs - prints an input string
 * @st: the string to be printed
 *
 * Return: Nothing
 */
void _wputs(char *st)
{
	int b = 0;

	if (!st)
		return;
	while (st[b] != '\0')
	{
		_wputchar(st[b]);
		b++;
	}
}

/**
 * _wputchar - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _wputchar(char ch)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buff[a++] = ch;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @ch: The character to print
 * @file_d: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char ch, int file_d)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(file_d, buff, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buff[a++] = ch;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @st: the string to be printed
 * @file_d: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *st, int file_d)
{
	int a = 0;

	if (!st)
		return (0);
	while (*st)
	{
		a += _putfd(*st++, file_d);
	}
	return (a);
}
