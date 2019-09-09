/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:08:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/09/07 18:55:51 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_lstinsert_at(t_list **head, t_list *node, size_t pos)
{
	size_t	i;
	t_list	*tmp_node;

	if (!pos)
	{
		node->next = *head;
		*head = node;
		return ;
	}
	tmp_node = *head;
	i = 0;
	while (++i < pos)
		tmp_node = tmp_node->next;
	node->next = tmp_node->next;
	tmp_node->next = node;
}