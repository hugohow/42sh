/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_apply_del.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:16:52 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/08 15:13:31 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_complete_apply_del(t_cmd *cmd)
{
	t_list	**head;

	if (!cmd->context->cursor)
		return (0);
	head = ft_complete_get_line(cmd->head);
	ft_lstdelnode(head, (cmd->context->cursor - 1));
	cmd->len -= 1;
	if (cmd->len < 0)
		cmd->len = 0;
	tputs(tgetstr("sc", NULL), 1, ft_putchar_stdin);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_stdin);
	ft_complete_print_line(cmd);
	cmd->context->width--;
	cmd->context->cursor--;
	tputs(tgetstr("rc", NULL), 1, ft_putchar_stdin);
	tputs(tgetstr("le", NULL), 1, ft_putchar_stdin);
	return (0);
}
