#include "shell.h"

void		ft_quote_add_printable(t_cmd *cmd, int c)
{
	t_list	*head;
	t_list	*node;
	int		i;

	head = ft_quote_get_line(cmd->head);
	i = 0;
	while (++i < cmd->arg->cursor)
		head = head->next;
	node = ft_lstnew((void*)&c, sizeof(int));	
	if (head)
	{
		node->next = head->next;
		head->next = node;
	}
	else
		ft_lstinsert(&cmd->head, node);
	cmd->size = cmd->size + 2;
	cmd->len = cmd->len + 1;
}

static void	check_default(t_cmd *cmd)
{
	struct winsize	w;
	int				col;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col = (cmd->arg->cursor + 8) + 1;
	col %= w.ws_col;
	if (!col)
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar_stdin);
		tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	}
	cmd->arg->cursor++;
}

int			ft_quote_apply_printable(t_cmd *cmd)
{
	if (!ft_isprint(cmd->last_key)
		&& cmd->last_key != KEY_TERM_CTRL_M)
		return (0);
	ft_quote_add_printable(cmd, cmd->last_key);
	ft_quote_print_line(cmd);
	check_default(cmd);
	cmd->arg->col++;
	return (0);
}