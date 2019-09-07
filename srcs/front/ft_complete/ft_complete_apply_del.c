/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_apply_del.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:16:52 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 15:00:12 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list		*ft_complete_get_line(t_list *head)
{
	t_list	*line;

	line = NULL;
	while (head)
	{
		if (head->content 
			&& *(char*)head->content == '\n')
			line = head->next;
		head = head->next;
	}
	return (line);
}

static void	display_cursor(t_cmd *cmd)
{
	struct winsize	w;
	int 			row;
	int				offset;
	char 			*cap;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	offset = strlen(cmd->context->prompt);
	row = (cmd->context->cursor + offset - 1) / w.ws_col;
	tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	while (row--)
		tputs(tgetstr("up", NULL), 1, ft_putchar_stdin);
	cap = tgetstr("DC", NULL);
	tputs(tgoto(cap, offset + cmd->context->cursor, 0), 1, ft_putchar_stdin);
}

void		ft_complete_print_line(t_cmd *cmd)
{
	t_list 	*head;
	size_t 	size;
	char 	*line;

	display_cursor(cmd);
	head = ft_complete_get_line(cmd->head);
	size = ft_lstlen(head);
	line = ft_node_join(head, size);
	if (!line)
		return ;
	ft_putstr_fd(cmd->context->prompt, 0);
	write(0, line, size);
	free(line);
}

int			ft_complete_apply_del(t_cmd *cmd)
{
	if (!cmd->context->cursor)
		return (0);
	cmd->len -= 1;
	if (cmd->len < 0)
		cmd->len = 0;
	ft_complete_print_line(cmd);
	cmd->context->cursor--;
	return (0);
}
