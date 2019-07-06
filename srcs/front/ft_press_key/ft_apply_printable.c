/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_printable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:57:13 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 19:34:54 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_apply_printable(t_cmd *cmd)
{
	t_list *head;
	t_list *node;

	if (ft_isprint(cmd->last_key))
	{
		head = cmd->head;
		write(0, &(cmd->last_key), sizeof(int));
		node = ft_lstnew((void *)&(cmd->last_key), sizeof(int));
		ft_lstinsert(&head, node);
		cmd->size = cmd->size + 2;
		cmd->len = cmd->len + 1;
		return (1);
	}
	return (1);
}