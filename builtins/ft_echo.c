/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:47:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/25 10:12:01 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to echo value
*/

static void clean_argv(char **argv)
{
	int i;
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
			clean_argv(argv);
		}
		i++;
	}
}

int ft_echo(int argc, char **argv, t_env **cpy_environ, int fds[])
{
    int i;
    int flag;

	(void)cpy_environ;
	(void)argc;
    i = 0;
    flag = 0;
    argv++;
	clean_argv(argv);
    while (argv[i])
    {
        ft_putstr_fd(argv[i], fds[1]);
		if (argv[i + 1])
        	ft_putchar_fd(' ', fds[1]);
        i++;
    }
	ft_putchar_fd('\n', fds[1]);
    return (0);
}