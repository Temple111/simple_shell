#include "eshell.h"


/**
 * **towstr - splits a string into words. Repeat delimiters are ignored
 * @st: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **towstr(char *st, char *del)
{
	int a, b, c, m, numwords = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; st[a] != '\0'; a++)
		if (!delim(st[a], del) && (delim(st[a + 1], del) || !st[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (delim(st[a], del))
			a++;
		c = 0;
		while (!delim(st[a + c], del) && st[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[b][m] = st[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **towstr2 - splits a string into words
 * @st: the input string
 * @del: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **towstr2(char *st, char del)
{
	int a, b, c, m, numwords = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (a = 0; st[a] != '\0'; a++)
		if ((st[a] != del && st[a + 1] == del) ||
		    (st[a] != del && !st[a + 1]) || st[a + 1] == del)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (st[a] == del && st[a] != del)
			a++;
		c = 0;
		while (st[a + c] != del && st[a + c] && st[a + c] != del)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[b][m] = st[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}
