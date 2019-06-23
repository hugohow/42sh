/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:40:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/23 11:19:00 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static t_ht * ft_get_table_bins(t_env **copy_environ)
{
	int i;

	i = 0;
	while (copy_environ[i])
	{
		if (ft_env_cmp_prefix("PATH", copy_environ[i]->line) == 0)
			return (copy_environ[i]->table);
		i++;
	}
	return (NULL);
}

static int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}


int ft_exe_bin(t_node *node, t_env ***p_environ, int fds[])
{
    int result_parsing;
	int result_cmd;
    char *command;
    char *new_path;
	char **args;

	result_parsing = 0;
	args = ft_get_args(node->cmd, *p_environ, &result_parsing);
	if (args[0] == NULL)
        return 0;
    command = ft_strtrim(args[0]);
    new_path = NULL;
    if (ft_is_path(command) == 1)
    {
		args[0] = ft_strcpy(args[0], "name");
        result_cmd = ft_exe_path(command, args, *p_environ, fds);
        return (ft_max(result_cmd, result_parsing));
    }
	if (ft_strcmp(command, "exit") == 0)
	{
		result_cmd = ft_exit(ft_list_size(args), args, *p_environ, fds);
		return (ft_max(result_cmd, result_parsing));
	}
    if (ft_strcmp(command, "echo") == 0)
    {
        result_cmd = ft_echo(ft_list_size(args), args, *p_environ, fds);
        return (ft_max(result_cmd, result_parsing));
    }
    if (ft_strcmp(command, "cd") == 0)
    {
		result_cmd = ft_cd(ft_list_size(args), args, p_environ, fds);
        return (ft_max(result_cmd, result_parsing));
    }
    if (ft_strcmp(command, "setenv") == 0)
    {
        result_cmd = ft_setenv(ft_list_size(args), args, p_environ, fds);
        return (ft_max(result_cmd, result_parsing));
    }
    if (ft_strchr(command, '='))
    {
		args[1] = ft_strdup(command);
		args[2] = 0;
        result_cmd = ft_setenv(ft_list_size(args), args, p_environ, fds);
        return (ft_max(result_cmd, result_parsing));
    }
    if (ft_strcmp(command, "unsetenv") == 0)
    {
        result_cmd = ft_unsetenv(ft_list_size(args), args, *p_environ, fds);
        return (ft_max(result_cmd, result_parsing));
    }
    if (ft_strcmp(command, "env") == 0)
    {
		result_cmd = ft_env(ft_list_size(args), args, *p_environ, fds);
        return (ft_max(result_cmd, result_parsing));
    }
	t_node_ht *value;
	t_ht *table_bins;
	table_bins = ft_get_table_bins(*p_environ);
	value = ft_ht_get(table_bins, command);
	if (value && (char *)(value->datum))
	{
		new_path = (char *)(value->datum);
		result_cmd = ft_exe_path(new_path, args, *p_environ, fds);
		return (ft_max(result_cmd, result_parsing));
	}
    else
    {

		DIR *pDir;
		struct dirent *pDirent;
		if ((pDir = opendir (".")))
		{
			while ((pDirent = readdir(pDir)) != NULL) 
			{
				if (ft_strcmp(pDirent->d_name, command) == 0)
				{
					new_path = ft_strjoin(getcwd(NULL, 0), "/");
					new_path = ft_strjoin(new_path, pDirent->d_name);
					result_cmd = ft_exe_path(new_path, args, *p_environ, fds);
					closedir (pDir);
					return (ft_max(result_cmd, result_parsing));
				}
			}
		}
		closedir (pDir);
		ft_dprintf(fds[2], "shell: command not found: %s\n", args[0]);
        return (EXIT_UTILITY_NOT_FOUND);
    }
    return (1);
}