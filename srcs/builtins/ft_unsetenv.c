/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:48:19 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 14:49:58 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to unset env variable
*/

int	ft_unsetenv(char **argv, t_env **cpy_environ, t_ht **p_hash, int fds[])
{
	int		i;
	int		argc;
	char	*prefix;
	t_vars	*p_vars;

	argc = (int)ft_list_size(argv);
	(void)p_hash;
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
			p_vars = ft_vars_get();
			ft_memdel((void **)&(p_vars->path_default));
			ft_ht_free(p_hash);
			*p_hash = NULL;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
