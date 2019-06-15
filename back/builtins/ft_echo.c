#include "shell.h"



int ft_echo(int argc, char **argv, char **cpy_environ, int fds[])
{
    int i;
    int flag_n;

    if (argc <= 1)
        return (0);
    if (cpy_environ)
    {

    }
    i = 0;
    flag_n = 0;
    argv++;
    if (argv[0] && ft_strcmp(argv[0], "-n") == 0)
    {
        flag_n = 1;
        i++;
    }
    while (argv[i])
    {
        ft_putstr_fd(argv[i], fds[1]);
        ft_putstr_fd(" ", fds[1]);
        i++;
    }
    if (flag_n)
    {

    }
    else
    {
     ft_putstr_fd("\n", fds[1]);   
    }
    return (0);
}