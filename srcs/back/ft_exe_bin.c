/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:40:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 01:24:13 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_search_and_exe_bin(t_node *node, t_env **cpy_environ, int fds[])
{
	int			result_cmd;
	t_node_ht	*value;
	char		*to_free;
	t_ht	**p_hash_table;

	p_hash_table = ft_p_bins_table_get();
	if (p_hash_table \
	&& *p_hash_table \
	&& (value = ft_ht_get(*p_hash_table, node->cmd_exec)) \
	&& value->datum)
	{
		to_free = (node->args)[0];
		(node->args)[0] = ft_strdup((char *)(value->datum));
		ft_memdel((void **)&to_free);
		result_cmd = ft_exe_path((node->args), cpy_environ, fds);
		return (result_cmd);
	}
	return (1);
}

int			ft_exe_bin(t_node *node, t_env ***p_env, int fds[])
{
	int		result_cmd;

	if (node->args == NULL || node->args[0] == NULL)
		return (1);
	if (ft_is_path(node->args[0]) == 1)
		result_cmd = ft_exe_path(node->args, *p_env, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_EXIT) == 0)
		result_cmd = ft_exit(node->args, p_env, fds);
	else if (ft_strcmp_lowercase(node->args[0], BUILTIN_ECHO) == 0)
		result_cmd = ft_echo(node->args, *p_env, fds);
	else if (ft_strcmp_lowercase(node->args[0], BUILTIN_CD) == 0)
		result_cmd = ft_cd(node->args, p_env, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_SETENV) == 0)
		result_cmd = ft_setenv(node->args, p_env, fds);
	else if (ft_strcmp(node->args[0], BUILTIN_UNSETENV) == 0)
		result_cmd = ft_unsetenv(node->args, *p_env, fds);
	else if (ft_strcmp_lowercase(node->args[0], BUILTIN_ENV) == 0)
		result_cmd = ft_env(node->args, *p_env, fds);
	else
		result_cmd = ft_search_and_exe_bin(node, *p_env, fds);
	return (result_cmd);
}
