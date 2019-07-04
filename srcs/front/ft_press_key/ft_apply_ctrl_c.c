/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_ctrl_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 03:03:27 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 17:36:57 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_apply_ctrl_c(t_cmd *cmd)
{
	t_list *head;
	t_list *node;
	int ret;
	
	head = cmd->head;
	ret = '\n';
	node = ft_lstnew((void *)&(ret), sizeof(ret));
	ft_lstinsert(&head, node);
	cmd->size = cmd->size + 2;
	cmd->len = 0;
	ft_putstr_fd("^C\n", 0);
	ft_interactive_prompt();
	return (1);
}