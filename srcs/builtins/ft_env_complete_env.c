/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_complete_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 00:39:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 19:56:59 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**ft_env_complete_env(char **argv, t_env ***p_copy_env, t_ht **p_hash)
{
	char	*prefix;
	char	*line;
	int		j;
	int		i;
	char	*to_free;

	j = -1;
	while ((argv)[++j] && ft_strchr((argv)[j], '=') != NULL)
	{
		i = 0;
		while (((argv)[j])[i] && ((argv)[j])[i] != '=')
			i++;
		prefix = ft_strsub((argv)[j], 0, i);
		line = (argv)[j] + i + 1;
		ft_env_add(prefix, line, p_copy_env);
		if (ft_strcmp(prefix, "PATH") == 0)
		{
			to_free = ft_strjoin_(prefix, "=", line);
			*p_hash = ft_bins_table_create(to_free);
			ft_memdel((void **)&to_free);
		}
		ft_memdel((void **)&prefix);
	}
	return (argv + j);
}
