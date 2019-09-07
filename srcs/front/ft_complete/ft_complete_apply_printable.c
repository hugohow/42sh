/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_apply_printable.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:32:02 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 18:34:58 by kesaint-         ###   ########.fr       */
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
	while (head && ++i < cmd->context->cursor)
		head = head->next;
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

static int 	is_right_margin(t_cmd *cmd)
{
	struct winsize	w;
	int				col;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col = cmd->context->cursor + ft_strlen(cmd->context->prompt) + 1;
	col %= w.ws_col;
	return (!col);
}

int		ft_complete_apply_printable(t_cmd *cmd)
{
	ft_complete_add_printable(cmd, cmd->last_key);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_stdin);
	ft_complete_print_line(cmd);
	tputs(tgetstr("rc", NULL), 1, ft_putchar_stdin);
	if (is_right_margin(cmd))
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar_stdin);
		tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar_stdin);
	cmd->context->cursor++;
	cmd->context->width++;
	return (0);
}
