/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:46:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 18:31:37 by hhow-cho         ###   ########.fr       */
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
	if (node && node->args)
	{
		i = 0;
		while (node->args[i])
		{
			ft_memdel((void **)(&(node->args[i])));
			i++;
		}
		ft_memdel((void **)(&(node->args)));
	}
	if (node && node->child)
	{
		i = 0;
		while (i < node->nb_child)
		{
			ft_syntax_tree_free(&(node->child[i]));
			i++;
		}
		ft_memdel((void **)(&(node->child)));
	}
	if (node)
		ft_memdel((void **)(&(node->cmd)));
	ft_memdel((void **)&node);
	ft_memdel((void **)&root);
}