/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:01:26 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 16:04:27 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsert(t_list **head, t_list *new_el)
{
	t_list *node;

	if (head == NULL)
		*head = new_el;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new_el;
	}
}
