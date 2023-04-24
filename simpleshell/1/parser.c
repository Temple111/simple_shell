#include "eshell.h"

/**
 * find_command - finds this cmd in the PATH string
 * @strpath: the PATH string
 * @cmd: the cmd to find
 * @f: the info struct
 *
 * Return: full path of cmd if found or NULL
 */
char *find_command(info_t *f, char *strpath, char *cmd)
{
	int ai = 0, current_pos = 0;
	char *path;

	if (!strpath)
		return (NULL);
	if ((_lenstr(cmd) > 2) && starts_hay(cmd, "./"))
	{
		if (is_cmd(f, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strpath[ai] || strpath[ai] == ':')
		{
			path = dup_chars(strpath, current_pos, ai);
			if (!*path)
				_catstr(path, cmd);
			else
			{
				_catstr(path, "/");
				_catstr(path, cmd);
			}
			if (is_cmd(f, path))
				return (path);
			if (!strpath[ai])
				break;
			current_pos = ai;
		}
		ai++;
	}
	return (NULL);
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
	int a = 0, b = 0;

	for (b = 0, a = begin; a < end; a++)
		if (strpath[a] != ':')
			buff[b++] = strpath[a];
	buff[b] = 0;
	return (buff);
}


/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
