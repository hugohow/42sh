#include "shell.h"

void ft_exit(int argc, char **argv, t_env **cpy_environ, int fds[])
{
    int i;

	(void)argc;
    if (argv[1])
    {
        if (argv[2])
        {
            ft_putstr_fd("Too many arguments Argument list too long", fds[2]);
            return ;
        }
        i = 0;
        while (argv[1][i] && argv[1][i] == ' ')
            i++;
        while (argv[1][i])
        {
            if (ft_isdigit(argv[1][i]) == 0)
            {
                ft_putstr_fd("Numeric argument required", fds[2]);
                exit(-1);
            }
            i++;
        }
        exit(ft_atoi(argv[1]));
    }   
	char *line;

	line = ft_env_get_line(cpy_environ, "?");
	if (line)
    	exit(ft_atoi(line + 2));
	exit(0);
}