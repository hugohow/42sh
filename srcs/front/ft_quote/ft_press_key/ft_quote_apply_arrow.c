#include "shell.h"

int		ft_quote_apply_arrow(t_cmd *cmd)
{
	if (cmd->last_key == KEY_TERM_RIGHT) 
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar_stdin);
		cmd->cursor++;
	}
	if (cmd->last_key == KEY_TERM_LEFT)
	{
		if (!cmd->cursor)
			return (0);
		cmd->cursor--;
		tputs(tgetstr("le", NULL), 1, ft_putchar_stdin);
	}
	return (0);
}