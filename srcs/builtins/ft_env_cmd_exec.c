/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 13:33:15 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/25 14:23:02 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_env_search_in_hash(char **argv, \
	t_ht **p_hash, t_env ***p_copy_env, int fds[])
{
	t_ht		*hash;
	t_node_ht	*value;
	char		*to_free;

	if (*p_hash)
		hash = *p_hash;
	else
		hash = *(ft_p_bins_table_get());
	if (hash \
		&& (value = ft_ht_get(hash, (argv)[0])) \
		&& value->datum)
	{
		to_free = (argv)[0];
		(argv)[0] = ft_strdup((char *)(value->datum));
		ft_memdel((void **)&to_free);
		return (ft_exe_path((argv), *p_copy_env, fds));
	}
	ft_dprintf(fds[2], "21sh env: command not found %s\n", argv[0]);
	return (EXIT_UTILITY_NOT_FOUND);
}

int			ft_env_cmd_exec(char **argv, \
	t_ht **p_hash, t_env ***p_copy_env, int fds[])
{
	int		i;

	i = 0;
	if (*argv)
	{
		if (ft_is_path(*argv) == 1)
			return (ft_exe_path(argv, *p_copy_env, fds));
		else
			return (ft_env_search_in_hash(argv, p_hash, p_copy_env, fds));
	}
	else
		ft_print_env(*p_copy_env, fds);
	return (i);
}
