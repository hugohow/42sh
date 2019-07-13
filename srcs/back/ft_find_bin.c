/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:31:24 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 12:31:40 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_search_in_curr_dir(char *cmd_exec)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;

	if ((p_dir = opendir(".")))
	{
		while ((p_dirent = readdir(p_dir)) != NULL)
		{
			if (ft_strcmp(p_dirent->d_name, cmd_exec) == 0)
			{
				closedir(p_dir);
				return (0);
			}
		}
		closedir(p_dir);
	}
	return (-1);
}

static int	ft_search_bin(char *cmd_exec, t_ht **p_table_bins)
{
	t_node_ht	*value;
	t_ht		**p_hash_table;

	if (*p_table_bins == NULL)
	{
		p_hash_table = ft_p_bins_table_get();
		if (p_hash_table \
		&& *p_hash_table \
		&& (value = ft_ht_get(*p_hash_table, cmd_exec)) \
		&& value->datum)
			return (0);
	}
	else
	{
		if (p_table_bins \
		&& *p_table_bins \
		&& (value = ft_ht_get(*p_table_bins, cmd_exec)) \
		&& value->datum)
			return (0);
	}
	return (ft_search_in_curr_dir(cmd_exec));
}

int			ft_find_bin(char *cmd_exec, t_ht **p_hash)
{
	if (cmd_exec == NULL)
		return (-1);
	if (ft_is_path(cmd_exec) == 1)
		return (0);
	else if (ft_strcmp(cmd_exec, BUILTIN_EXIT) == 0)
		return (0);
	else if (ft_strcmp_lowercase(cmd_exec, BUILTIN_ECHO) == 0)
		return (0);
	else if (ft_strcmp_lowercase(cmd_exec, BUILTIN_CD) == 0)
		return (0);
	else if (ft_strcmp(cmd_exec, BUILTIN_SETENV) == 0)
		return (0);
	else if (ft_strcmp(cmd_exec, BUILTIN_UNSETENV) == 0)
		return (0);
	else if (ft_strcmp_lowercase(cmd_exec, BUILTIN_ENV) == 0)
		return (0);
	return (ft_search_bin(cmd_exec, p_hash));
}
