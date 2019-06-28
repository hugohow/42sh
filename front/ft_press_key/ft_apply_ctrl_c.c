/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_ctrl_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 03:03:27 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 22:33:25 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_apply_ctrl_c(t_cmd *cmd, int to_write)
{
	t_list *head;
	t_list *node;
	int ret;
	
	head = cmd->head;
	if (to_write)
		write(0, "^C", 2);
	ret = '\n';
	node = ft_lstnew((void *)&(ret), sizeof(ret));
	ft_lstinsert(&head, node);
	cmd->size = cmd->size + 2;
	cmd->len = 0;
	ft_putstr_fd("\n", 0);
	ft_terminal_prompt();
	return (1);
}