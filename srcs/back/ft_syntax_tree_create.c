/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:55:53 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 23:27:57 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		node->child = get_child(node, node->cmd, copy_env);
		if (node->child == NULL)
		{
			node->type = TYPE_CMD;
		}
	}
	return (node);
}

t_node		**get_child(t_node *node, char *cmd, t_env **copy_env)
{
	t_node **child;

	child = ft_get_semi_colon_child(node, cmd, copy_env);
	if (child == NULL)
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = 2;
	return (child);
}

t_node		*ft_syntax_tree_create(char *cmd, t_env **copy_env)
{
	t_node *root;

	if (cmd == NULL || ft_strlen(cmd) == 0)
		return (NULL);
	root = create_node(TYPE_BASE, cmd, copy_env);
	return (root);
}
