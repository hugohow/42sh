/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:19:11 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/19 21:33:28 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

int ft_setenv(int argc, char **argv, t_env ***p_environ, int fds[])
{
    if (argc > 3)
    {
        ft_putstr_fd("setenv: Too many arguments.\n", fds[2]);
        return (EXIT_FAIL);
    }
    if (argc == 1)
    {
        ft_print_env(*p_environ, fds);
        return (EXIT_SUCCESS);
    }
    if (ft_isdigit(argv[1][0]))
    {
        ft_putstr_fd("not valid. must begin with a letter\n", fds[2]);
        return (EXIT_FAIL);
    }
    if (argc == 2)
    {
        int i;

        i = 0;
        while (argv[1][i] && argv[1][i] != '=')
            i++;
        ft_env_add(ft_strsub(argv[1], 0, i), argv[1] + i + 1, p_environ);
    }
    else
    {
        ft_env_add(argv[1], argv[2], p_environ);
    }

    return (EXIT_SUCCESS);
}