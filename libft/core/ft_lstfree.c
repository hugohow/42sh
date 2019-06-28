/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:22:38 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 14:05:29 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list *head)
{
	t_list *node;
	t_list *next;

	node = head;
	next = node->next;
	while (node != NULL)
	{
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
