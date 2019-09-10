/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:56:17 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 19:20:53 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_current_col(t_context *context)
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

int		ft_move_cursor_right(t_cmd *cmd)
{
	int		col;

	if (cmd->context->cursor == cmd->context->width)
		return (0);
	col = get_current_col(cmd->context);
	if (col)
		tputs(tgetstr("nd", NULL), 1, ft_putchar_stdin);
	else
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar_stdin);
		tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	}
	cmd->context->cursor++;
	return (0);
}

int		ft_move_cursor_left(t_cmd *cmd)
{
	int				col;
	char			*cap;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!cmd->context->cursor)
		return (0);
	col = get_current_col(cmd->context);
	if (col == 1)
	{
		cap = tgetstr("ch", NULL);
		tputs(tgoto(cap, 0, w.ws_col), 1, ft_putchar_stdin);
		tputs(tgetstr("up", NULL), 1, ft_putchar_stdin);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar_stdin);
	cmd->context->cursor--;
	return (0);
}

int			ft_move_cursor_begin(t_cmd *cmd)
{
	struct winsize	w;
	int				cursor;
	int				offset;
	char			*cap;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	offset = ft_strlen(cmd->context->prompt);
	cursor = cmd->context->cursor;
	cursor += offset;
	if (cursor > w.ws_col)
	{
		offset = 0;
		cmd->context->cursor -= (cursor % w.ws_col);
	}
	else
		cmd->context->cursor = 0;
	tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	cap = tgetstr("ch", NULL);
	tputs(tgoto(cap, 0, offset), 1, ft_putchar_stdin);
	return (0);
}

int			ft_move_cursor_end(t_cmd *cmd)
{
	struct winsize	w;
	int				offset;
	char			*cap;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	offset = (cmd->context->cursor + w.ws_col);
	if (offset < cmd->context->width)
	{
		cap = tgetstr("ch", NULL);
		cmd->context->cursor = w.ws_col;
		tputs(tgoto(cap, 0, w.ws_col), 1, ft_putchar_stdin);
		return (0);
	}
	offset = (cmd->context->width - cmd->context->cursor);
	cmd->context->cursor += offset;
	cap = tgetstr("RI", NULL);
	tputs(tgoto(cap, 0, offset), 1, ft_putchar_stdin);
	return (0);
}