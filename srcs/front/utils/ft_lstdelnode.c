/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:08:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/09/07 18:55:51 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_lstdelnode(t_list **head, size_t pos)
{
	size_t	i;
	t_list	*item;
	t_list	*next;

	if (!pos)
	{
		item = *head;
		*head = item->next;
		free(item);
		return ;
	}
	item = *head;
	i = 0;
	while (item->next && ++i < pos)
		item = item->next;
	next = item->next;
	item->next = next->next;
	free(next);
}