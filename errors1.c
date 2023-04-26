#include "eshell.h"

/**
 * _erratoi - converts a string to an integer
 * @st: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *st)
{
	int a = 0;
	unsigned long int rst = 0;

	if (*st == '+')
		st++;  /* TODO: why does this make main return 255? */
	for (a = 0;  st[a] != '\0'; a++)
	{
		if (st[a] >= '0' && st[a] <= '9')
		{
			rst *= 10;
			rst += (st[a] - '0');
			if (rst > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rst);
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
	_wputs(f->f_name);
	_wputs(": ");
	print_decimal(f->err_count, STDERR_FILENO);
	_wputs(": ");
	_wputs(f->argv[0]);
	_wputs(": ");
	_wputs(estrg);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @inp: the input
 * @file_d: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int inp, int file_d)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _abs_, curr;

	if (file_d == STDERR_FILENO)
		__putchar = _wputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inp;
	curr = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + curr / a);
			count++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * convert_num- converter function, a clone of itoa
 * @numb: number
 * @bs: base
 * @flg: argument flags
 *
 * Return: string
 */
char *convert_num(long int numb, int bs, int flg)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *pt;
	unsigned long n = numb;

	if (!(flg & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	arr = flg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
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

/**
 * replace_hash - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void replace_hash(char *buff)
{
	int a;

	for (a = 0; buff[a] != '\0'; a++)
		if (buff[a] == '#' && (!a || buff[a - 1] == ' '))
		{
			buff[a] = '\0';
			break;
		}
}
