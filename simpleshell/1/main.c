#include "eshell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t f[] = { INFO_INIT };
	int file_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_d)
		: "r" (file_d));

	if (ac == 2)
	{
		file_d = open(av[1], O_RDONLY);
		if (file_d == -1)
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
		f->readfd = file_d;
	}
	populate_envlinked_list(f);
	read_hist(f);
	hsh(f, av);
	return (EXIT_SUCCESS);
}
