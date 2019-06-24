/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:55:53 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/24 21:24:34 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node *create_node(long type, char *cmd, t_env **copy_env)
{
    t_node *node;

    if (!(node = ft_memalloc(sizeof(t_node))))
		return (NULL);
    node->type = type;
    node->cmd = ft_strdup(cmd);
	node->args = NULL;
    if (type & TYPE_CMD)
        node->child = NULL;
	else
	{
		node->child = get_child(cmd, copy_env);
		if (node->child == NULL && ft_strcmp(cmd, ";") != 0)
			node->type = TYPE_CMD;
	}
    return (node);
}

t_node **get_child(char *cmd, t_env **copy_env)
{
    t_node **child;

    child = ft_get_semi_colon_child(cmd, copy_env);
    return (child);
}



t_node **ft_syntax_tree_create(char *cmd, t_env **copy_env)
{
    t_node **root;

	if (cmd == NULL || ft_strlen(cmd) == 0)
		return (NULL);
    if (!(root = (t_node **)ft_memalloc(sizeof(t_node *))))
		return (NULL);
    *root = create_node(TYPE_BASE, cmd, copy_env);
    return (root);
}