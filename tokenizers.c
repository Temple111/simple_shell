#include "eshell.h"

/**
 * **towstr- splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **towstr(char *string, char *del)
{
	int a, b, c, d, numwd = 0;
	char **sm;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; string[a] != '\0'; a++)
		if (!delim(string[a], del) && (delim(string[a + 1], del) || !string[a + 1]))
			numwd++;

	if (numwd == 0)
		return (NULL);
	sm = malloc((1 + numwd) * sizeof(char *));
	if (!sm)
		return (NULL);
	for (a = 0, b = 0; b < numwd; b++)
	{
		while (delim(string[a], del))
			a++;
		c = 0;
		while (!delim(string[a + c], del) && string[a + c])
			c++;
		sm[b] = malloc((c + 1) * sizeof(char));
		if (!sm[b])
		{
			for (c = 0; c < b; c++)
				free(sm[c]);
			free(sm);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			sm[b][d] = string[a++];
		sm[b][d] = 0;
	}
	sm[b] = NULL;
	return (sm);
}

/**
 * **towstr2 - splits a string into words
 * @string: the input string
 * @del: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **towstr2(char *string, char del)
{
	int a, b, c, d, numwd = 0;
	char **sm;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (a = 0; string[a] != '\0'; a++)
		if ((string[a] != del && string[a + 1] == del) ||
		    (string[a] != del && !string[a + 1]) || string[a + 1] == del)
			numwd++;
	if (numwd == 0)
		return (NULL);
	sm = malloc((1 + numwd) * sizeof(char *));
	if (!sm)
		return (NULL);
	for (a = 0, b = 0; b < numwd; b++)
	{
		while (string[a] == del && string[a] != del)
			a++;
		c = 0;
		while (string[a + c] != del && string[a + c] && string[a + c] != del)
			c++;
		sm[b] = malloc((c + 1) * sizeof(char));
		if (!sm[b])
		{
			for (c = 0; c < b; c++)
				free(sm[c]);
			free(sm);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			sm[b][d] = string[a++];
		sm[b][d] = 0;
	}
	sm[b] = NULL;
	return (sm);
}
