/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_semi_colon_child.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 02:45:56 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 13:55:47 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node **ft_get_semi_colon_child(char *cmd, t_env **copy_env)
{
    char **list;
    int k;
    t_node **child;

    list = ft_strsplit(cmd, ';');
    k = 0;
    child = NULL;
    if (list[0] && list[1])
    {
        child = malloc(999*sizeof(t_node *));
        while (list[k])
        {
            child[k] = create_node(TYPE_SEPARATOR, list[k], copy_env);
            k++;
        }
        child[k] = 0;
    }
    if (k == 0)
        return (NULL);
    return (child);
}