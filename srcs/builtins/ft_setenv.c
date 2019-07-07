/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:19:11 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 14:34:01 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

/*
** Builtin to set env variable
*/

static int handle_errors(int argc, char **argv, int fds[])
{
	if (argc == 1)
		return (0);
    if (argc > 3)
    {
        ft_putstr_fd("setenv: Too many arguments.\n", fds[2]);
        return (EXIT_FAIL);
    }
    if (ft_isdigit(argv[1][0]))
    {
        ft_putstr_fd("not valid. must begin with a letter\n", fds[2]);
        return (EXIT_FAIL);
    }
	return (0);
}

int ft_setenv(char **argv, t_env ***p_environ, t_ht **p_table_bins, int fds[])
{
	int argc;
	char *prefix;
	char *line;
	int i;

	argc = (int)ft_list_size(argv);
    if ((i = handle_errors(argc, argv, fds)) != 0)
		return (i);
	i = 0;
    if (argc == 1)
        ft_print_env(*p_environ, fds);
    else if (argc == 2)
    {
        while (argv[1][i] && argv[1][i] != '=')
            i++;
		prefix = ft_strsub(argv[1], 0, i);
		line = argv[1] + i + 1;
        ft_env_add(prefix, line, p_environ);
        if (ft_strcmp("PATH", prefix) == 0)
        {
            ft_ht_free(p_table_bins);
            *p_table_bins = ft_bins_table_create(line);
        }
		ft_memdel((void **)&prefix);
    }
    else
    {
		prefix = argv[1];
		line = argv[2];
        ft_env_add(prefix, line, p_environ);
        if (ft_strcmp("PATH", prefix) == 0)
        {
            ft_ht_free(p_table_bins);
            *p_table_bins = ft_bins_table_create(line);
        }
    }
    return (EXIT_SUCCESS);
}