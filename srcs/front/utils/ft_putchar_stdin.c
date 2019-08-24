#include "shell.h"

int		ft_putchar_stdin(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}