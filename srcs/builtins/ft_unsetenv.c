/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:48:19 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 10:59:02 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_error(int fds[])
{
	ft_putstr_fd("unsetenv: Too few arguments.\n", fds[2]);
	return (EXIT_FAIL);
}

/*
** Builtin to unset env variable
*/

int			ft_unsetenv(char **argv, t_env **cpy_env, int fds[])
{
	int		i;
	int		argc;
	char	*prefix;
	t_vars	*p_vars;
	t_ht	**p_hash;

 	p_hash = ft_p_bins_table_get();
	argc = (int)ft_list_size(argv);
	if (argc == 1)
		return (handle_error(fds));
	i = 1;
	while (i < argc)
	{
		prefix = argv[i];
		ft_env_delete_line(prefix, cpy_env);
		if (ft_strcmp(prefix, "PATH") == 0)
		{
			p_vars = ft_vars_get();
			ft_memdel((void **)&(p_vars->path_default));
			ft_ht_free(p_hash);
			*p_hash = NULL;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
