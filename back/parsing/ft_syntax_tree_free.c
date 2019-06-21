/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:46:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/21 14:00:55 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_syntax_tree_free(t_node **root)
{
	t_node *node;
	int i;

	if (root == NULL)
		return ;
	node = *root;
	i = 0;
	if (node->child)
	{
		while (node->child[i])
		{
			ft_syntax_tree_free(&(node->child[i]));
			i++;
		}
		ft_memdel((void **)(node->child));
	}
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			ft_memdel((void **)(node->args[i]));
			i++;
		}
		ft_memdel((void **)(node->args));
	}
	ft_memdel((void **)(&(node->cmd)));
	ft_memdel((void **)root);
}