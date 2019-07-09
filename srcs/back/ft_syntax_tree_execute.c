/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_execute.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:45:16 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 17:24:38 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_init_args(t_node *node, t_env ***p_environ)
{
	int res_parse;

	res_parse = 0;
	node->args = ft_args_get(node->cmd, *p_environ, &res_parse);
	if (node->args == NULL || node->args[0] == NULL)
	{
		ft_list_free(&(node->args));
		return (1);
	}
	return (0);
}

static void	ft_exec_node_cmd(t_node *node, t_env ***p_env, \
	t_ht **p_hash, int fds[])
{
	int	success;

	if ((ft_find_bin(node, p_hash)) < 0)
	{
		ft_dprintf(fds[2], \
			"minishell: command not found: %s\n", node->cmd_exec);
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = EXIT_UTILITY_NOT_FOUND;
	}
	else if ((ft_init_args(node, p_env)) == 1)
	{
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = 1;
	}
	else
	{
		success = ft_exe_bin(node, p_env, p_hash, fds);
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = success;
	}
}

void		ft_syntax_tree_execute(t_node *node, t_env ***p_env, \
	t_ht **p_hash, int fds[])
{
	int k;

	if (node == NULL)
		return ;
	if (node && node->type & TYPE_CMD)
	{
		ft_exec_node_cmd(node, p_env, p_hash, fds);
	}
	k = 0;
	if (node && node->child && node->child[k])
	{
		while (node->child[k])
		{
			ft_syntax_tree_execute(node->child[k], p_env, p_hash, fds);
			if ((node->child[k])->args == NULL)
				return ;
			if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
				return ;
			k++;
		}
	}
}
