/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:40:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 20:18:09 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int ft_search_and_exe_bin(char **args, t_env **cpy_environ, int fds[])
{
	int result_cmd;
	char *command;
	t_node_ht *value;
	t_ht *table_bins;
	char *to_free;

	table_bins = ft_bins_table_get(cpy_environ);
	command = args[0];
	if (table_bins && (value = ft_ht_get(table_bins, args[0])) && value->datum)
	{
		to_free = args[0];
		args[0] = ft_strdup((char *)(value->datum));
		ft_memdel((void **)&to_free);
		result_cmd = ft_exe_path(args, cpy_environ, fds);
	}
	else
	{
		DIR *pDir;
		struct dirent *pDirent;
		if ((pDir = opendir (".")))
		{
			while ((pDirent = readdir(pDir)) != NULL) 
			{
				if (ft_strcmp(pDirent->d_name, args[0]) == 0)
				{
					char *cwd;

					cwd = *((char **)ft_vars_get_value(KEY_CWD));
					to_free = args[0];
					args[0] = ft_strjoin_(cwd, "/", pDirent->d_name);
					ft_memdel((void **)&(to_free));
					result_cmd = ft_exe_path(args, cpy_environ, fds);
					closedir (pDir);
					return (result_cmd);
				}
			}
			closedir (pDir);
		}
		ft_dprintf(fds[2], "minishell: command not found: %s\n", args[0]);
		result_cmd = EXIT_UTILITY_NOT_FOUND;
	}
	return (result_cmd);
}



int ft_exe_bin(t_node *node, t_env ***p_environ, int fds[])
{
    int result_parsing;
	int result_cmd;
    char *command;
	char *new_path;

	result_parsing = 0;
	node->args = ft_get_args(node->cmd, *p_environ, &result_parsing);
	if (node->args == NULL)
		return (1);
	if (node->args[0] == NULL)
        return 0;
    new_path = NULL;
	command = node->args[0];
	result_cmd = 0;
    if (ft_is_path(command) == 1)
		result_cmd = ft_exe_path(node->args, *p_environ, fds);
	else if (ft_strcmp(command, BUILTIN_EXIT) == 0)
		result_cmd = ft_exit(node->args, p_environ, fds);
    else if (ft_strcmp(command, BUILTIN_ECHO) == 0)
        result_cmd = ft_echo(node->args, *p_environ, fds);
    else if (ft_strcmp(command, BUILTIN_CD) == 0)
		result_cmd = ft_cd(node->args, p_environ, fds);
    else if (ft_strcmp(command, BUILTIN_SETENV) == 0)
        result_cmd = ft_setenv(node->args, p_environ, fds);
    else if (ft_strcmp(command, BUILTIN_UNSETENV) == 0)
        result_cmd = ft_unsetenv(node->args, *p_environ, fds);
    else if (ft_strcmp(command, BUILTIN_ENV) == 0)
		result_cmd = ft_env(node->args, *p_environ, fds);
	else
		result_cmd = ft_search_and_exe_bin(node->args, *p_environ, fds);
	return (ft_max(result_cmd, result_parsing));
}