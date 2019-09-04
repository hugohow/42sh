#include "shell.h"

static int		get_current_col(t_cmd *cmd)
{
	struct winsize	w;
	int				col;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col = (cmd->arg->cursor + 8) + 1;
	return (col % w.ws_col);
}

static void		right_call(t_cmd *cmd)
{
	int				col;

	col = get_current_col(cmd);
	if (cmd->arg->cursor == cmd->arg->col)
		return ;
	if (!col)
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar_stdin);
		tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar_stdin);
	cmd->arg->cursor++;
}

static void	left_call(t_cmd *cmd)
{
	struct winsize	w;
	int				col;
	char			*cap;

	if (!cmd->arg->cursor)
		return ;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	fprintf(stdin, "\n\n%i\n", w.ws_col);
	col = (cmd->arg->cursor + 8) + 1;
	col %= w.ws_col;
	if (col == 1)
	{
		cap = tgetstr("ch", NULL);
		tputs(tgoto(cap, 0, w.ws_col), 1, ft_putchar_stdin);
		tputs(tgetstr("up", NULL), 1, ft_putchar_stdin);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar_stdin);
	cmd->arg->cursor--;
}

int		ft_quote_apply_arrow(t_cmd *cmd)
{
	if (cmd->last_key == KEY_TERM_RIGHT) 
		right_call(cmd);
	if (cmd->last_key == KEY_TERM_LEFT)
		left_call(cmd);
	return (0);
}