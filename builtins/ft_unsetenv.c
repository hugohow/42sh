/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:49:18 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 15:01:40 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

/*
** Builtin to unset env variable
*/

int ft_unsetenv(int argc, char **argv, t_env **cpy_environ, int fds[])
{
    int i;

    if (argc == 1)
    {
        ft_putstr_fd("unsetenv: Too few arguments.\n", fds[2]);
        return (EXIT_FAIL);
    }
    i = 1;
    while (i < argc)
    {
        ft_env_delete_line(argv[i], cpy_environ);
        i++;
    }
    return (EXIT_SUCCESS);
}