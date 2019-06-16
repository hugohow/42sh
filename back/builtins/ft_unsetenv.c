/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:49:18 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 14:00:08 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"


int ft_unsetenv(int argc, char **argv, t_env **cpy_environ, int fds[])
{
    int i;

    if (argc == 1)
    {
        ft_putstr_fd("unsetenv: Too few arguments.\n", fds[2]);
        return (0);
    }
    i = 1;
    while (i < argc)
    {
        ft_delete_line_env(argv[i], cpy_environ);
        i++;
    }    

    return (0);
}