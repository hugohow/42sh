/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:47:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/21 01:55:59 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to echo value
*/

int ft_echo(int argc, char **argv, t_env **cpy_environ, int fds[])
{
    int i;
    int flag;

	(void)cpy_environ;
	(void)argc;
    i = 0;
    flag = 0;
    argv++;
    // if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
    // {
    //     flag = FLAG_ECHO_N;
    //     i++;
    // }
    while (argv[i])
    {
        ft_putstr_fd(argv[i], fds[1]);
		if (argv[i + 1])
        	ft_putchar_fd(' ', fds[1]);
        i++;
    }
    // if (flag == 0)
		ft_putchar_fd('\n', fds[1]);
    return (0);
}