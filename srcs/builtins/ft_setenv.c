/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:39:43 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 01:04:13 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_errors_init(int argc, char **argv, int fds[])
{
	int i;

	if (argc == 1)
		return (0);
	if (argc > 3)
	{
		ft_putstr_fd("setenv: Too many arguments\n", fds[2]);
		return (EXIT_FAIL);
	}
	if (ft_isdigit(argv[1][0]))
	{
		ft_putstr_fd("setenv: not valid. must begin with a letter\n", fds[2]);
		return (EXIT_FAIL);
	}
	i = -1;
	while (argv[1][++i])
	{
		if (ft_isalnum(argv[1][i]) == 0 && argv[1][i] != '_')
		{
			ft_putstr_fd(\
				"setenv: Must contain alphanumeric characters\n", fds[2]);
			return (EXIT_FAIL);
		}
	}
	return (0);
}

static void	set_env_two_args(char *prefix, char *line,\
	t_ht **p_table_bins, t_env ***p_environ)
{
	char	*to_free;

	ft_env_add(prefix, line, p_environ);
	if (ft_strcmp("PATH", prefix) == 0)
	{
		ft_ht_free(p_table_bins);
		to_free = ft_strjoin_(prefix, "=", line);
		*p_table_bins = ft_bins_table_create(to_free);
		ft_memdel((void **)&to_free);
	}
}

int			ft_setenv(char **argv, t_env ***p_environ, int fds[])
{
	int		argc;
	char	*prefix;
	char	*line;
	int		i;
	t_ht	**p_hash;

	p_hash = ft_p_bins_table_get();
	argc = (int)ft_list_size(argv);
	if ((i = handle_errors_init(argc, argv, fds)) != 0)
		return (i);
	i = 0;
	if (argc == 1)
		ft_print_env(*p_environ, fds);
	else if (argc == 2)
	{
		prefix = argv[1];
		ft_env_add(prefix, "", p_environ);
		if (ft_strcmp("PATH", prefix) == 0)
			ft_ht_free(p_hash);
	}
	else
	{
		prefix = argv[1];
		line = argv[2];
		set_env_two_args(prefix, line, p_hash, p_environ);
	}
	return (EXIT_SUCCESS);
}
