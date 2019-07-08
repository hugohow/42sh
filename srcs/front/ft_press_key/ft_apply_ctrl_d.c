/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_ctrl_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 03:18:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 22:43:38 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_apply_ctrl_d(t_cmd *cmd)
{
	t_list	*head;
	t_list	*node;

	if (cmd->len == 0)
	{
		head = cmd->head;
		write(0, "exit", 4);
		node = ft_lstnew((void *)"exit", 5);
		ft_lstinsert(&head, node);
		cmd->size = cmd->size + 6;
		return (0);
	}
	return (1);
}
