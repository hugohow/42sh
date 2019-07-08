/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:22:38 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 14:25:04 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list *head)
{
	t_list *node;
	t_list *next;

	node = head;
	if (node == NULL)
		return ;
	next = node->next;
	while (node != NULL)
	{
		if (node->content)
			ft_memdel((void **)&(node->content));
		node->content_size = 0;
		ft_memdel((void **)&node);
		node = next;
		if (node)
			next = node->next;
		else
			next = NULL;
	}
}
