#include "shell.h"

int		ft_quote_apply_key(t_cmd *cmd)
{
	int key;

	key = cmd->last_key;
	if (key == KEY_TERM_RIGHT || key == KEY_TERM_LEFT)
		return (ft_quote_apply_arrow(cmd));
	if (key == KEY_TERM_DEL)
		return (ft_quote_apply_del(cmd));
	if (key == KEY_TERM_ENTER)
		return (ft_quote_apply_enter(cmd));
	return (ft_quote_apply_printable(cmd));
}