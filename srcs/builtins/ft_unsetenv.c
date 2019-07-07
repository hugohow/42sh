/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:49:18 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 14:33:34 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

/*
** Builtin to unset env variable
*/

int ft_unsetenv(char **argv, t_env **cpy_environ, t_ht **p_table_bins, int fds[])
{
    int i;
	int argc;
	char *prefix;
    
	argc = (int)ft_list_size(argv);
    if (argc == 1)
    {
        ft_putstr_fd("unsetenv: Too few arguments.\n", fds[2]);
        return (EXIT_FAIL);
    }
    i = 1;
    while (i < argc)
    {
		prefix = argv[i];
        ft_env_delete_line(prefix, cpy_environ);
        if (ft_strcmp(prefix, "PATH") == 0)
	    {
		    ft_ht_free(p_table_bins);
	    }
        i++;
    }
    return (EXIT_SUCCESS);
}