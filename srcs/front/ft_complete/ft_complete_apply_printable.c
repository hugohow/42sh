/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_apply_printable.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:32:02 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 14:51:47 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_complete_add_printable(t_cmd *cmd, int c)
{
	t_list	*head;
	t_list	*node;
	int		i;

	i = 0;
	head = ft_complete_get_line(cmd->head);
	while (head && i < cmd->context->cursor) 
	{
		i++;
		head = head->next;
	}
	node = ft_lstnew((void*)&c, sizeof(int));
	if (head)
	{
		node->next = head->next;
		head->next = node;
	}
	else 
		ft_lstinsert(&cmd->head, node);
	cmd->size += 2;
	cmd->len++;
}

int		ft_complete_apply_printable(t_cmd *cmd)
{
	ft_complete_add_printable(cmd, cmd->last_key);
	ft_complete_print_line(cmd);
	cmd->context->cursor++;
	//cmd->arg->col++;
	return (0);
}
