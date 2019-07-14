/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_execute.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:45:16 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 11:04:12 by hhow-cho         ###   ########.fr       */
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

static int	ft_exec_node_cmd(t_node *node, t_env ***p_env, int fds[])
{
	int	success;

	if (node->cmd_exec == NULL)
	{
		return (1);
	}
	else if ((ft_find_bin(node->cmd_exec)) < 0)
	{
		ft_dprintf(fds[2], \
			"minishell: command not found: %s\n", node->cmd_exec);
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = EXIT_UTILITY_NOT_FOUND;
		return (1);
	}
	else if ((ft_init_args(node, p_env)) == 1)
	{
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = 1;
		return (-1);
	}
	else
	{
		success = ft_exe_bin(node, p_env, fds);
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = success;
		return (success);
	}
}

int			ft_syntax_tree_execute(t_node *node, t_env ***p_env, int fds[])
{
	int k;

	if (node == NULL)
		return (0);
	if (node && node->type & TYPE_CMD)
	{
		return (ft_exec_node_cmd(node, p_env, fds));
	}
	k = 0;
	if (node && node->child && node->child[k])
	{
		while (node->child[k])
		{
			if ((ft_syntax_tree_execute(node->child[k], p_env, fds)) < 0)
				return (1);
			if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
				return (0);
			k++;
		}
	}
	return (0);
}
