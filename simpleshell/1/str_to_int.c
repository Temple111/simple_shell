#include "eshell.h"

/**
 * str_to_int - converts a string to an integer
 * @str: pointer to address of string
 * Return: 0 for success
 */

int str_to_int(char *str)
{
	int n = 0, sign = 1, in = 0;

	if (str[0] == '-')
	{
		sign = -1;
		in++;
	}
	while (str[in] != '\0')
	{
		if (str[in] >= '0' && str[in] <= '9')
		{
			n = n * 10 + (str[in] - '0');
			in++;
		}
		else
		{
			break;
		}
	}
	n = n * sign;
	return (n);
}
/**
 * delim - checks if character is a delimeter
 * @ch: the char to check
 * @del: the delimeter string
 * Return: 0 for success
 */

int delim(char ch, char *del)
{
	int in = 0;

	while (del[in] != '\0')
	{
		if (ch == del[in])
		{
			return (1);
		}
		in++;
	}
	return (0);
}
/**
 * shell_inter - checks if shell is in interactive mode
 * @sh: struct address
 *
 * Return: 0 for success
 */

int shell_inter(info_t *sh)
{
	return (isatty(STDIN_FILENO) && sh->readfd <= 2);
}

/**
 * isAlphabetic - checks if a character is alphbetic
 * @ch: the character to be inputed
 * Return: 0 after success
 */

int isAlphabetic(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
