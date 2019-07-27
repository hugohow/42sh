/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:55:53 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/25 23:38:11 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_child(t_node *node, t_env **copy_env)
{
	int ret;

	if ((ret = (ft_get_semi_colon_child(node, copy_env))) > 0)
		return (ret);
	if (node->child)
		return (ret);
	if ((ret = (ft_get_pipe_child(node, copy_env))) > 0)
		return (ret);
	return (ret);
}
t_node		*create_node(long type, char *cmd, t_env **copy_env)
{
	t_node *node;

	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		return (NULL);
	node->type = type;
	node->cmd = ft_strdup(cmd);
	node->cmd_exec = NULL;
	node->args = NULL;
	node->nb_child = -1;
	if (type & TYPE_CMD)
	{
		node->cmd_exec = ft_args_get_first(cmd, copy_env);
		node->child = NULL;
	}
	else
	{
		if ((get_child(node, copy_env)) > 0)
			node->type = TYPE_CMD;
		else
		{
			if (node->child == NULL)
			{
				node->type = TYPE_CMD;
				node->cmd_exec = ft_args_get_first(cmd, copy_env);
			}
		}
	}
	return (node);
}

t_node		*ft_syntax_tree_create(char *cmd, t_env **copy_env)
{
	t_node *root;

	if (cmd == NULL || ft_strlen(cmd) == 0)
		return (NULL);
	root = create_node(TYPE_BASE, cmd, copy_env);
	return (root);
}
