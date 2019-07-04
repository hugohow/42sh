/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:46:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/02 03:50:39 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_syntax_tree_free(t_node **p_root)
{
	t_node *node;
	int i;

	if (p_root == NULL || *p_root == NULL)
		return ;
	node = *p_root;
	if (node->child)
	{
		i = 0;
		while (i < node->nb_child)
		{
			ft_syntax_tree_free(&(node->child[i]));
			i++;
		}
		ft_memdel((void **)(&(node->child)));
	}
	ft_memdel((void **)(&(node->cmd)));
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			ft_memdel((void **)(&(node->args[i])));
			i++;
		}
		ft_memdel((void **)(&(node->args)));
	}
	ft_memdel((void **)&node);
}