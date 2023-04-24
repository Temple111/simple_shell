#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delim - checks if character is a delimeter
 * @a: the char to check
 * @del: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delim(char a, char *del)
{
	while (*del)
		if (*del++ == a)
			return (1);
	return (0);
}

/**
 *isAlphabetic - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int isAlphabetic(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *str_to_int - converts a string to an integer
 *@st: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int str_to_int(char *st)
{
	int j, sign = 1, fg = 0, output;
	unsigned int rst = 0;

	for (j = 0;  st[j] != '\0' && fg != 2; j++)
	{
		if (st[j] == '-')
			sign *= -1;

		if (st[j] >= '0' && st[j] <= '9')
		{
			fg = 1;
			rst *= 10;
			rst += (st[j] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sign == -1)
		output = -rst;
	else
		output = rst;

	return (output);
}
