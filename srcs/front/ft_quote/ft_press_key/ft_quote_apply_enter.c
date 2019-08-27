#include "shell.h"

int		ft_quote_apply_enter(t_cmd *cmd)
{
	tputs(tgetstr("nw", NULL), 1, ft_putchar_stdin);
	ft_quote_add_printable(cmd, '\n');
	tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	ft_putstr_fd("\n", 0);
	ft_putstr_fd(cmd->arg->prompt, 0);
	cmd->arg->cursor = 0;
	cmd->arg->col = 0;
	return (0);
}