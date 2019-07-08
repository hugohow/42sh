/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:40:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 18:29:06 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	ft_search_in_curr_dir(char **args, t_env **cpy_environ, int fds[])
{
	int				result_cmd;
	DIR				*p_dir;
	struct dirent	*p_dirent;
	char			*cwd;
	char			*to_free;

	if ((p_dir = opendir(".")))
	{
		while ((p_dirent = readdir(p_dir)) != NULL)
		{
			if (ft_strcmp(p_dirent->d_name, args[0]) == 0)
			{
				cwd = *((char **)ft_vars_get_value(KEY_CWD));
				to_free = args[0];
				args[0] = ft_strjoin_(cwd, "/", p_dirent->d_name);
				ft_memdel((void **)&(to_free));
				result_cmd = ft_exe_path(args, cpy_environ, fds);
				closedir(p_dir);
				return (result_cmd);
			}
		}
		closedir(p_dir);
	}
	ft_dprintf(fds[2], "minishell: command not found: %s\n", args[0]);
	return (EXIT_UTILITY_NOT_FOUND);
}

static int	ft_search_and_exe_bin(char **args, t_env **cpy_environ,\
	t_ht **p_table_bins, int fds[])
{
	int			result_cmd;
	char		*command;
	t_node_ht	*value;
	char		*to_free;

	command = args[0];
	if (p_table_bins \
	&& *p_table_bins \
	&& (value = ft_ht_get(*p_table_bins, args[0])) \
	&& value->datum)
	{
		to_free = args[0];
		args[0] = ft_strdup((char *)(value->datum));
		ft_memdel((void **)&to_free);
		result_cmd = ft_exe_path(args, cpy_environ, fds);
		return (result_cmd);
	}
	result_cmd = ft_search_in_curr_dir(args, cpy_environ, fds);
	return (result_cmd);
}

static int	ft_init_args(t_node *node, t_env ***p_environ, \
	int *p_res_parse, int *p_result_cmd)
{
	*p_res_parse = 0;
	*p_result_cmd = 0;
	node->args = ft_args_get(node->cmd, *p_environ, p_res_parse);
	if (node->args == NULL || node->args[0] == NULL)
	{
		ft_list_free(&(node->args));
		return (1);
	}
	return (0);
}

int			ft_exe_bin(t_node *node, t_env ***p_env, t_ht **p_hash, int fds[])
{
	int		res_parse;
	int		result_cmd;

	if (ft_init_args(node, p_env, &res_parse, &result_cmd) == 1)
		return (1);
	if (ft_is_path(node->args[0]) == 1)
		result_cmd = ft_exe_path(node->args, *p_env, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_EXIT) == 0)
		result_cmd = ft_exit(node->args, p_env, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_ECHO) == 0)
		result_cmd = ft_echo(node->args, *p_env, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_CD) == 0)
		result_cmd = ft_cd(node->args, p_env, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_SETENV) == 0)
		result_cmd = ft_setenv(node->args, p_env, p_hash, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_UNSETENV) == 0)
		result_cmd = ft_unsetenv(node->args, *p_env, p_hash, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_ENV) == 0)
		result_cmd = ft_env(node->args, *p_env, fds);
	else
		result_cmd = ft_search_and_exe_bin(node->args, *p_env, p_hash, fds);
	return (ft_max(result_cmd, res_parse));
}
