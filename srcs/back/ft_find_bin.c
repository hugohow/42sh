/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:31:24 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 11:34:02 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	traverse_paths(char **paths, char *cmd_exec)
{
	int	i;
	DIR				*p_dir;
	struct dirent	*p_dirent;
	t_ht	**p_hash_table;
	char	*new_path;

	p_hash_table = ft_p_bins_table_get();
	i = 0;
	while (paths[i])
	{
		if ((p_dir = opendir(paths[i])))
		{
			while ((p_dirent = readdir(p_dir)) != NULL)
			{
				if (ft_strcmp(p_dirent->d_name, cmd_exec) == 0)
				{
					new_path = ft_strjoin_(paths[i], "/", p_dirent->d_name);
					ft_ht_add(*p_hash_table, p_dirent->d_name, (void *)(new_path));
					ft_memdel((void **)&new_path);	
					ft_list_free(&paths);
					closedir(p_dir);
					return (0);
				}
			}
		}
		closedir(p_dir);
		i++;
	}
	ft_list_free(&paths);
	return (-1);
}

static int	ft_search_again(char *cmd_exec)
{
	char		*line;
	char		**paths;
	t_env	***p_copy_env;

	p_copy_env = ft_vars_get_p_copy_env();
	if ((line = ft_env_get_value(*p_copy_env, "PATH")))
	{
		paths = ft_str_separate(line, ':');
		if (paths == NULL)
			return (EXIT_UTILITY_NOT_FOUND);
		return (traverse_paths(paths, cmd_exec));
	}
	return (-1);
}


static int	ft_search_bin(char *cmd_exec)
{
	t_node_ht	*value;
	t_ht	**p_table_bins;

 	p_table_bins = ft_p_bins_table_get();
	if (p_table_bins \
	&& *p_table_bins \
	&& (value = ft_ht_get(*p_table_bins, cmd_exec)) \
	&& value->datum)
		return (0);
	return (ft_search_again(cmd_exec));
}

int			ft_find_bin(char *cmd_exec)
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
	return (ft_search_bin(cmd_exec));
}
