/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:56:17 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 15:29:46 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_get_current_column(t_context *context)
{
	struct winsize	w;
	int				column;
	int				offset;

	offset = 1;
	if (context->prompt)
		offset += ft_strlen(context->prompt);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	column = (context->cursor + offset);
	column %= w.ws_col;
	return (column);
}

static void	ft_move_cursor_right(t_cmd *cmd)
{
	int	col;

	if (cmd->context->cursor == cmd->context->width)
		return ;
	col = ft_get_current_column(cmd->context);
	if (!col)
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar_stdin);
		tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar_stdin);
	cmd->context->cursor++;
}

static void	ft_move_cursor_left(t_cmd *cmd)
{
	int				column;
	char			*cap;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!cmd->context->cursor)
		return ;
	column = ft_get_current_column(cmd->context);
	if (column == 1)
	{
		cap = tgetstr("ch", NULL);
		tputs(tgoto(cap, 0, w.ws_col), 1, ft_putchar_stdin);
		tputs(tgetstr("up", NULL), 1, ft_putchar_stdin);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar_stdin);
	cmd->context->cursor--;
}

int			ft_move_cursor(t_cmd *cmd)
{
	if (cmd->last_key == KEY_TERM_RIGHT)
		ft_move_cursor_right(cmd);
	if (cmd->last_key == KEY_TERM_LEFT)
		ft_move_cursor_left(cmd);
	return (0);
}
