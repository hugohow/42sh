/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_execute.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:45:16 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/29 19:09:24 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int    ft_exec_loop_pipe(t_node	**child, t_env ***p_env, int fds[]) 
{
	int   p[2];
	pid_t pid;
	int   fd_in;

	fd_in = 0;
	while (*child != NULL)
	{
		pipe(p);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(fd_in, 0); //change the input according to the old one 
			if (*(child + 1) != NULL)
			dup2(p[1], 1);
			close(p[0]);
			if ((ft_syntax_tree_execute(*child, p_env, fds)) < 0)
				return (1);
				exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			fd_in = p[0]; //save the input for the next command
			child++;
		}
	}
	return (0);
}

int			ft_syntax_tree_execute(t_node *node, t_env ***p_env, int fds[])
{
	int k;

	if (node == NULL)
		return (0);
	if (node && node->type & TYPE_CMD)
		return (ft_syntax_tree_execute_node(node, p_env, fds));
	k = 0;
	if (node && node->type & TYPE_OR && node->child && node->child[k])
	{
		while (node->child[k])
		{
			if ((ft_syntax_tree_execute(node->child[k], p_env, fds)) < 0)
				return (1);
			if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
				return (0);
			if (*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) == 0)
				break ;
			k++;
		}
	}
	if (node && node->type & TYPE_AND && node->child && node->child[k])
	{
		while (node->child[k])
		{
			if ((ft_syntax_tree_execute(node->child[k], p_env, fds)) < 0)
				return (1);
			if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
				return (0);
			if (*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) != 0)
				break ;
			k++;
		}
	}
	if (node && node->type & TYPE_SEMI_COLON && node->child && node->child[k])
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
	else if (node && node->type & TYPE_PIPE && node->child && node->child[k])
	{
		if (ft_exec_loop_pipe(node->child, p_env, fds) != 0)
			return (1);
	}
	return (0);
}
