#include "shell.h"



int ft_echo(int argc, char **argv, t_env **cpy_environ, int fds[])
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
	int j;

	i = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
		{
			j = i + 1;
			while (argv[j])
			{
				argv[j - 1] = argv[j];
				j++;
			}
			argv[j - 1] = 0;
		}
		i++;
	}
	i = 0;
    while (argv[i])
    {
        ft_putstr_fd(argv[i], fds[1]);
		if (argv[i + 1])
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