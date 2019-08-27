#include "shell.h"

int		ft_quote_apply_arrow(t_cmd *cmd)
{
	struct winsize	w;
	int		cursor;

	ioctl(STDOUT_FILENO, TIOCGWINCH, &w);
	cursor = cmd->arg->cursor;
	if (cursor)
		cursor %= w.ws_col;
	if (cmd->last_key == KEY_TERM_RIGHT) 
	{
		if (cmd->arg->cursor == cmd->arg->col)
			return (0);
		tputs(tgetstr("nd", NULL), 1, ft_putchar_stdin);
		cmd->arg->cursor++;
	}
	if (cmd->last_key == KEY_TERM_LEFT)
	{
		if (!cmd->arg->cursor)
				return (0);
		cmd->arg->cursor--;
		tputs(tgetstr("le", NULL), 1, ft_putchar_stdin);
	}
	return (0);
}