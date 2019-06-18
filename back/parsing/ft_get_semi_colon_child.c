/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_semi_colon_child.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 02:45:56 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/18 14:13:47 by hhow-cho         ###   ########.fr       */
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

static void free_list(char **list)
{
	size_t i;

	i = 0;
	while (list[i])
	{
		ft_memdel((void **)(&(list[i])));
		i++;
	}
}

t_node **ft_get_semi_colon_child(char *cmd, t_env **copy_env)
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
			free_list(list);
			return (NULL);
		}
        while (list[k])
        {
            child[k] = create_node(TYPE_SEPARATOR, list[k], copy_env);
            k++;
        }
        child[k] = 0;
    }
	ft_memdel((void **)(list));
    return (child);
}