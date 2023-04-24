#include "shell.h"

/**
 * main - entry point
 * @ag: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ag, char **av)
{
	info_t f[] = { INFO_INIT };
	int op = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (op)
		: "r" (op));

	if (ag == 2)
	{
		op = open(av[1], O_RDONLY);
		if (op == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_wputs(av[0]);
				_wputs(": 0: Can't open ");
				_wputs(av[1]);
				_wputchar('\n');
				_wputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		f->readfd = op;
	}
	populate_envlinked_list(f);
	read_hist(f);
	hsh(f, av);
	return (EXIT_SUCCESS);
}
