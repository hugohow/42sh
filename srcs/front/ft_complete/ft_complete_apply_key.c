#include "shell.h"

static const	t_fts_apply g_fcts[] =
{
	{KEY_TERM_ENTER, &ft_complete_apply_enter},
	{KEY_TERM_RIGHT, &ft_move_cursor_right},
	{KEY_TERM_LEFT, &ft_move_cursor_left},
	{KEY_TERM_HOME, &ft_move_cursor_begin},
	{KEY_TERM_END, &ft_move_cursor_end},
	{KEY_TERM_DEL, &ft_complete_apply_del},
	{0, &ft_complete_apply_printable},
};

int				ft_complete_apply_key(t_cmd *cmd)
{
	int				i;
	t_ft_apply		*ft;

	i = 0;
	while (g_fcts[i].key)
	{
		if (g_fcts[i].key == cmd->last_key)
		{
			ft = g_fcts[i].fct;
			return (ft(cmd));
		}
		i++;
	}
	ft = g_fcts[i].fct;
	return (ft(cmd));
}
