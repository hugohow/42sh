/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:47:49 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 14:15:02 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node *create_node(long type, char *cmd, t_env **copy_env)
{
    t_node *node;

    node = ft_memalloc(sizeof(t_node));
    node->type = type;
    node->cmd = ft_strdup(cmd);
	node->args = NULL;
    // if type pipe;
    // only 2 child
    if (type & TYPE_CMD)
    {
		node->args = ft_get_args(cmd, copy_env);
        node->child = NULL;
        return (node);
    }
    node->child = get_child(cmd, copy_env);
    if (node->child == NULL)
    {
        node->child = malloc(sizeof(t_node *) * 2);
        node->child[0] = create_node(TYPE_CMD, cmd, copy_env);
        node->child[1] = 0;
    }
    return (node);
}

t_node **get_child(char *cmd, t_env **copy_env)
{
    t_node **child;

    child = ft_get_semi_colon_child(cmd, copy_env);

    return (child);
}



t_node **ft_parse_cmd(char *cmd, t_env **copy_env)
{
    t_node **root;

	if (cmd == NULL || ft_strlen(cmd) == 0)
		return (0);
    root = malloc(sizeof(t_node *));
    *root = create_node(TYPE_BASE, cmd, copy_env);


    return (root);
}