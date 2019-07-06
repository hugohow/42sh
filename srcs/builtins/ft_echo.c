/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:47:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 18:47:55 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to echo value
*/

static char **clean_argv(char **argv)
{
	int i;
	int j;

	char **argv_cpy;

	i = 0;
	while (argv[i])
		i++;
	argv_cpy = (char **)ft_memalloc((i + 1) * sizeof(char *));
	if (argv_cpy == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) != 0)
		{
			argv_cpy[j] = argv[i];
			j++;
		}
		i++;
	}
	return (argv_cpy);
}

int ft_echo(char **argv, t_env **cpy_environ, int fds[])
{
    int i;
    int flag;
	char **argv_cpy;

	(void)cpy_environ;
    i = 0;
    flag = 0;
    argv++;
	argv_cpy = clean_argv(argv);
    while (argv_cpy[i])
    {
        ft_putstr_fd(argv_cpy[i], fds[1]);
		if (argv_cpy[i + 1])
        	ft_putchar_fd(' ', fds[1]);
        i++;
    }
	ft_putchar_fd('\n', fds[1]);
	ft_memdel((void **)&argv_cpy);
    return (0);
}