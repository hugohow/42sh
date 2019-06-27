/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_semi_colon_child.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 02:45:56 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 18:51:20 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t list_len(char **list)
{
	size_t i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

t_node **ft_get_semi_colon_child(t_node *node, char *cmd, t_env **copy_env)
{
    char **list;
    int k;
    t_node **child;

    if (!(list = ft_strsplit(cmd, ';')))
		return (NULL);
    k = 0;
    child = NULL;
    if (list && list[0])
    {
        if (!(child = (t_node **)ft_memalloc((list_len(list) + 1) * sizeof(t_node *))))
		{
			ft_list_free(&list);
			return (NULL);
		}
        while (list[k])
        {
            child[k] = create_node(TYPE_CMD, list[k], copy_env);
			if (child[k] == NULL)
				break ;
            k++;
        }
		node->nb_child = k;
        child[k] = 0;
		ft_list_free(&list);
    }
    return (child);
}