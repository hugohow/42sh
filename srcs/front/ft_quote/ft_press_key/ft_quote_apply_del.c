#include "shell.h"

t_list		*ft_quote_get_line(t_list *head)
{
	t_list	*line;

	line = NULL;
	while (head)
	{
		if (head->content 
			&& *(char*)head->content == '\n')
			line = head->next;
		head = head->next;
	}
	return (line);
}

void		ft_quote_print_line(t_cmd *cmd)
{
	t_list				*head;
	size_t				size;
	char				*line;

	tputs(tgetstr("cb", NULL), 1, ft_putchar_stdin);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	ft_putstr_fd("dquote> ", 0);
	head = ft_quote_get_line(cmd->head);
	size = ft_lstlen(head);
	if (!(line = ft_node_join(head, size)))
		return ;
	write(0, line, size);
	free(line);
}

int			ft_quote_apply_del(t_cmd *cmd)
{
	t_list		*head;

	if (!cmd->cursor)
		return (0);
	head = ft_quote_get_line(cmd->head);
	ft_lstdelnode(&head, (cmd->cursor - 1));
	cmd->len = cmd->len - 1;
	if (cmd->len < 0)
		cmd->len = 0;
	ft_quote_print_line(cmd);
	cmd->cursor--;
	return (0);
}
