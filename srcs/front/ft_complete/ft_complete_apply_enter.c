#include "shell.h"

int		ft_complete_apply_enter(t_cmd *cmd)
{
	tputs(tgetstr("nw", NULL), 1, ft_putchar_stdin);
	ft_complete_add_printable(cmd, '\n');
	tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	ft_putstr_fd("\n", 0);
	ft_putstr_fd(cmd->arg->prompt, 0);
	cmd->context->cursor = 0;
	return (0);
}