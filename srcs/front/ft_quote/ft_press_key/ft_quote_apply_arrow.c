#include "shell.h"

static void		right_call(t_cmd *cmd)
{
	struct winsize	w;
	int				col;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col = (cmd->arg->cursor + 8);
	if (cmd->arg->cursor > w.ws_col)
		col %= w.ws_col;
	if (cmd->arg->cursor == cmd->arg->col)
		return ;
	if (col + 1 == w.ws_col)
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar_stdin);
		tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar_stdin);
	cmd->arg->cursor++;
}

static void 	left_call(t_cmd *cmd)
{
	if (!cmd->arg->cursor)
		return ;
	cmd->arg->cursor--;
	tputs(tgetstr("le", NULL), 1, ft_putchar_stdin);
}

int		ft_quote_apply_arrow(t_cmd *cmd)
{
	if (cmd->last_key == KEY_TERM_RIGHT) 
		right_call(cmd);
	if (cmd->last_key == KEY_TERM_LEFT)
		left_call(cmd);
	return (0);
}