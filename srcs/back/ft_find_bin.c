/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:31:24 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 13:29:56 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	add_to_ht(char *key, char *path, DIR *p_dir, char **paths)
{
	ft_ht_add(*ft_p_bins_table_get(), key, (void *)(path));
	ft_memdel((void **)&path);
	ft_list_free(&paths);
	closedir(p_dir);
	return (0);
}

static int	traverse_paths(char **paths, char *cmd_exec)
{
	int				i;
	DIR				*p_dir;
	struct dirent	*p_dirent;
	char			*new_path;

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
					return (add_to_ht(p_dirent->d_name, \
						new_path, p_dir, paths));
				}
			}
			closedir(p_dir);
		}
		i++;
	}
	ft_list_free(&paths);
	return (-1);
}

static int	ft_search_again(char *cmd_exec, t_env ***p_env)
{
	char		*line;
	char		**paths;

	if ((line = ft_env_get_value(*p_env, "PATH")))
	{
		paths = ft_str_separate(line, ':');
		if (paths == NULL)
			return (-1);
		return (traverse_paths(paths, cmd_exec));
	}
	return (-1);
}

static int	ft_search_bin(char *cmd_exec, t_env ***p_env)
{
	t_node_ht	*value;
	t_ht		**p_table_bins;

	p_table_bins = ft_p_bins_table_get();
	if (p_table_bins \
	&& *p_table_bins \
	&& (value = ft_ht_get(*p_table_bins, cmd_exec)) \
	&& value->datum)
		return (0);
	return (ft_search_again(cmd_exec, p_env));
}

int			ft_find_bin(char *cmd_exec, t_env ***p_env)
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
	return (ft_search_bin(cmd_exec, p_env));
}
