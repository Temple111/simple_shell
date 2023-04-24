#include "shell.h"

/**
 * _shexit - exits the shell
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _shexit(info_t *f)
{
	int exit_check;

	if (f->argv[1])  /* If there is an exit arguement */
	{
		exit_check = _erratoi(f->argv[1]);
		if (exit_check == -1)
		{
			f->status = 2;
			print_errmessage(f, "Illegal number: ");
			_wputs(f->argv[1]);
			_wputchar('\n');
			return (1);
		}
		f->err_num = _erratoi(f->argv[1]);
		return (-2);
	}
	f->err_num = -1;
	return (-2);
}

/**
 * _chcd - changes the current directory of the process
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _chcd(info_t *f)
{
	char *sh, *dr, buff[1024];
	int chdr_ret;

	sh = getcwd(buff, 1024);
	if (!sh)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!f->argv[1])
	{
		dr = _get_env(f, "HOME=");
		if (!dr)
			chdr_ret = /* TODO: what should this be? */
				chdir((dr = _get_env(f, "PWD=")) ? dr : "/");
		else
			chdr_ret = chdir(dr);
	}
	else if (_cmpstr(f->argv[1], "-") == 0)
	{
		if (!_get_env(f, "OLDPWD="))
		{
			_puts(sh);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(f, "OLDPWD=")), _putchar('\n');
		chdr_ret = /* TODO: what should this be? */
			chdir((dr = _get_env(f, "OLDPWD=")) ? dr : "/");
	}
	else
		chdr_ret = chdir(f->argv[1]);
	if (chdr_ret == -1)
	{
		print_errmessage(f, "can't cd to ");
		_wputs(f->argv[1]), _wputchar('\n');
	}
	else
	{
		_setenv(f, "OLDPWD", _get_env(f, "PWD="));
		_setenv(f, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _chcdp - changes the current directory of the process
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _chcdp(info_t *f)
{
	char **arg_arr;

	arg_arr = f->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}
