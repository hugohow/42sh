/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:47:49 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/09 02:59:59 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node *create_node(long type, char *cmd)
{
    t_node *node;

    node = ft_memalloc(sizeof(t_node));
    node->type = type;
    node->cmd = cmd;
    // if type pipe;
    // only 2 child
    if (type & TYPE_CMD)
    {
        node->child = NULL;
        return (node);
    }
    node->child = get_child(cmd);
    if (node->child == NULL)
    {
        node->child = malloc(sizeof(t_node *) * 2);
        node->child[0] = create_node(TYPE_CMD, cmd);
        node->child[1] = 0;
    }
    return (node);
}

t_node **get_child(char *cmd)
{
    t_node **child;

    child = ft_get_semi_colon_child(cmd);

    return (child);
}



int ft_parse_cmd(char *cmd, char ***copy_env, int prev_res)
{
    t_node **root;
    int success;

    root = malloc(sizeof(t_node *));
    *root = create_node(TYPE_BASE, cmd);

    success = prev_res;

    execute_tree(*root, get_paths(*copy_env), copy_env,  0, 1, 2, &success);

    return (success);
}