#include "eshell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @f: the info struct
 * @path_file: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *f, char *path_file)
{
	struct stat st;

	(void)f;
	if (!path_file || stat(path_file, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @strpath: the PATH string
 * @begin: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *strpath, int begin, int end)
{
	static char buff[1024];
	int a = 0, c = 0;

	for (c = 0, a = begin; a < end; a++)
		if (strpath[a] != ':')
			buff[c++] = strpath[a];
	buff[c] = 0;
	return (buff);
}

/**
 * find_command - finds this cmd in the PATH string
 * @f: the info struct
 * @strpath: the PATH string
 * @cm_d: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_command(info_t *f, char *strpath, char *cm_d)
{
	int a = 0, current_pos = 0;
	char *path;

	if (!strpath)
		return (NULL);
	if ((_lenstr(cm_d) > 2) && starts_hay(cm_d, "./"))
	{
		if (is_cmd(f, cm_d))
			return (cm_d);
	}
	while (1)
	{
		if (!strpath[a] || strpath[a] == ':')
		{
			path = dup_chars(strpath, current_pos, a);
			if (!*path)
				_catstr(path, cm_d);
			else
			{
				_catstr(path, "/");
				_catstr(path, cm_d);
			}
			if (is_cmd(f, path))
				return (path);
			if (!strpath[a])
				break;
			current_pos = a;
		}
		a++;
	}
	return (NULL);
}
