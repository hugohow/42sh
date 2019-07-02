/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:19:11 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 01:09:17 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

/*
** Builtin to set env variable
*/

int ft_setenv(char **argv, t_env ***p_environ, int fds[])
{
	int argc;

	argc = (int)ft_list_size(argv);
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
		char *prefix;

        i = 0;
        while (argv[1][i] && argv[1][i] != '=')
            i++;
		prefix = ft_strsub(argv[1], 0, i);
        ft_env_add(prefix, argv[1] + i + 1, p_environ, 0);
		ft_memdel((void **)&prefix);
    }
    else
    {
        ft_env_add(argv[1], argv[2], p_environ, 0);
    }

    return (EXIT_SUCCESS);
}