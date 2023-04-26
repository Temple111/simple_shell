#include "eshell.h"

/**
 * hsh - main shell loop
 * @f: the parameter & return info struct
 * @ag: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *f, char **ag)
{
	ssize_t c = 0;
	int builtin_rt = 0;

	while (c != -1 && builtin_rt != -2)
	{
		clear_info(f);
		if (interactive(f))
			_puts("$ ");
		_wputchar(BUFF_FLUSH);
		c = get_input(f);
		if (c != -1)
		{
			set_info(f, ag);
			builtin_rt = find_built_in(f);
			if (builtin_rt == -1)
				cmd_find(f);
		}
		else if (interactive(f))
			_putchar('\n');
		free_info(f, 0);
	}
	write_hist(f);
	free_info(f, 1);
	if (!interactive(f) && f->ret_status)
		exit(f->ret_status);
	if (builtin_rt == -2)
	{
		if (f->err_code == -1)
			exit(f->ret_status);
		exit(f->err_code);
	}
	return (builtin_rt);
}

/**
 * find_built_in - finds a builtin command
 * @f: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_built_in(info_t *f)
{
	int a, built_in_rt = -1;
	builtin_table builtintbl[] = {
		{"exit", _shexit},
		{"env", _curr_env},
		{"help", _chcdp},
		{"history", _disphist},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _chcd},
		{"alias", _alias_mimic},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].flag_type; a++)
		if (_cmpstr(f->argv[0], builtintbl[a].flag_type) == 0)
		{
			f->err_count++;
			built_in_rt = builtintbl[a].func(f);
			break;
		}
	return (built_in_rt);
}

/**
 *cmd_find - finds a command in PATH
 * @f: the parameter & return info struct
 *
 * Return: void
 */
void cmd_find(info_t *f)
{
	char *path = NULL;
	int a, c;

	f->str_path = f->argv[0];
	if (f->lineinput_count == 1)
	{
		f->err_count++;
		f->lineinput_count = 0;
	}
	for (a = 0, c = 0; f->argu[a]; a++)
		if (!delim(f->argu[a], " \t\n"))
			c++;
	if (!c)
		return;

	path = find_command(f, _get_env(f, "PATH="), f->argv[0]);
	if (path)
	{
		f->str_path = path;
		cmd_find(f);
	}
	else
	{
		if ((interactive(f) || _get_env(f, "PATH=")
			|| f->argv[0][0] == '/') && is_cmd(f, f->argv[0]))
			cmd_fork(f);
		else if (*(f->argu) != '\n')
		{
			f->ret_status = 127;
			print_errmessage(f, "not found\n");
		}
	}
}

/**
 * cmd_fork - forks a an exec thread to run cmd
 * @f: the parameter & return info struct
 *
 * Return: void
 */
void cmd_fork(info_t *f)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(f->str_path, f->argv, get_env(f)) == -1)
		{
			free_info(f, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(f->ret_status));
		if (WIFEXITED(f->ret_status))
		{
			f->ret_status = WEXITSTATUS(f->ret_status);
			if (f->ret_status == 126)
				print_errmessage(f, "Permission denied\n");
		}
	}
}
