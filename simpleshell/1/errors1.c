#include "eshell.h"

/**
 * replace_hash - function replaces first instance of '#' with '\0'
 * @str: address of the string to modify
 *
 * Return: Always 0;
 */

void replace_hash(char *str)
{
	char *ph = str;

	while (*ph != '\0')
	{
		if (*ph == '#')
		{
			*ph = '\0';
			break;
		}
		ph++;
	}
}
/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(const char *str)
{
	bool is_negative = false;
	int result = 0;

	if (*str == '-')
	{
		is_negative = true;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		++str;
	}
	return (is_negative ? -result : result);
}
/**
 * print_errmessage - prints an error message
 * @f: the parameter & return info struct
 * @estrg: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_errmessage(info_t *f, char *estrg)
{
	_wputs(f->fname);
	_wputs(": ");
	print_decimal(f->line_count, STDERR_FILENO);
	_wputs(": ");
	_wputs(f->argv[0]);
	_wputs(": ");
	_wputs(estrg);
}
/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @in: the input
 * @d: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int in, int d)
{
	int (*__putchar)(char) = _putchar;
	int a, increase = 0;
	unsigned int _abs_, curr;

	if (d == STDERR_FILENO)
		__putchar = _wputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		increase++;
	}
	else
		_abs_ = in;
	curr = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + curr / a);
			increase++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	increase++;

	return (increase);
}

/**
 * convert_num - converter function, a clone of itoa
 * @numb: number
 * @bs: base
 * @fg: argument flags
 *
 * Return: string
 */
char *convert_num(long int numb, int bs, int fg)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *pt;
	unsigned long n = numb;

	if (!(fg & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	arr = fg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buff[49];
	*pt = '\0';

	do	{
		*--pt = arr[n % bs];
		n /= bs;
	} while (n != 0);

	if (sign)
		*--pt = sign;
	return (pt);
}
