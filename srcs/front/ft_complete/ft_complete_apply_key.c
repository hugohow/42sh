#include "shell.h"

int		ft_complete_apply_key(t_cmd *cmd)
{
	int		key;

	key = cmd->last_key;
	if (key == KEY_TERM_RIGHT || key == KEY_TERM_LEFT
		|| key == KEY_TERM_HOME || key == KEY_TERM_END)
		return (ft_move_cursor(cmd));
	if (key == KEY_TERM_DEL)
		return (ft_complete_apply_del(cmd));
	if (key == KEY_TERM_ENTER)
		return (ft_complete_apply_enter(cmd));
	return (ft_complete_apply_printable(cmd));
}