/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_execute_node.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 21:28:04 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/25 21:30:13 by hhow-cho         ###   ########.fr       */
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

int	ft_syntax_tree_execute_node(t_node *node, t_env ***p_env, int fds[])
{
	int	success;

	if (node->cmd_exec == NULL)
	{
		return (1);
	}
	else if ((ft_find_bin(node->cmd_exec, p_env)) < 0)
	{
		ft_dprintf(fds[2], \
			"21sh: command not found: %s\n", node->cmd_exec);
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