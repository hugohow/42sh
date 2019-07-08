/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_semi_colon_child.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:46:08 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 16:50:57 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node	**ft_get_semi_colon_child(t_node *node, char *cmd, t_env **copy_env)
{
	char	**list;
	int		k;
	t_node	**child;

	if (!(list = ft_strsplit(cmd, ';')))
		return (NULL);
	child = NULL;
	if (list && list[0])
	{
		if (!(child = (t_node **)ft_memalloc((ft_list_size(list) + 1)\
			* sizeof(t_node *))))
		{
			ft_list_free(&list);
			return (NULL);
		}
		k = -1;
		while (list[++k])
		{
			if (!(child[k] = create_node(TYPE_CMD, list[k], copy_env)))
				break ;
		}
		node->nb_child = k;
	}
	ft_list_free(&list);
	return (child);
}
