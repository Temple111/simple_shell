#include "eshell.h"

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
 * @fdes: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char ch, int fdes)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fdes, buff, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buff[a++] = ch;
	return (1);
}
/**
 *_putsfd - prints an input string
 * @string: the string to be printed
 * @fdes: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *string, int fdes)
{
	int a = 0;

	if (!string)
		return (0);
	while (*string)
	{
		a += _putfd(*string++, fdes);
	}
	return (a);
}
/**
 *_wputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _wputs(char *str)
{
	char *ph = str;

	while (*ph != '\0')
	{
		_wputchar(*ph);
		ph++;
	}
	_wputchar('\n');
}
