/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_apply_del.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:16:52 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/04 16:16:54 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list		*ft_quote_get_line(t_list *head)
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

void		ft_quote_print_line(t_cmd *cmd)
{
	t_list				*head;
	size_t				size;
	char				*line;
	char				*cap;
	struct winsize		w;
	int					row;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	row = ((cmd->arg->cursor + 7) / w.ws_col);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	while (row--)
		tputs(tgetstr("up", NULL), 1, ft_putchar_stdin);
	cap = tgetstr("DC", NULL);
	tputs(tgoto(cap, 7 + cmd->arg->cursor, 0), 1, ft_putchar_stdin);
	ft_putstr_fd(cmd->arg->prompt, 0);
	head = ft_quote_get_line(cmd->head);
	size = ft_lstlen(head);
	if (!(line = ft_node_join(head, size)))
		return ;
	write(0, line, size);
	free(line);
}

int			ft_complete_apply_del(t_cmd *cmd)
{
	t_list		*head;

	if (!cmd->context->cursor)
		return (0);
	cmd->len -= 1;
	if (cmd->len < 0)
		cmd->len = 0;
	cmd->arg->cursor--;
	return (0);
}

// int			ft_quote_apply_del(t_cmd *cmd)
// {
// 	t_list		*head;

// 	if (!cmd->arg->cursor)
// 		return (0);
// 	head = ft_quote_get_line(cmd->head);
// 	ft_lstdelnode(&head, (cmd->arg->cursor - 1));
// 	cmd->len = cmd->len - 1;
// 	if (cmd->len < 0)
// 		cmd->len = 0;
// 	ft_quote_print_line(cmd);
// 	cmd->arg->cursor--;
// 	return (0);
// }
