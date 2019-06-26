/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_get_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/26 23:45:54 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/*
** Read one line of stdin (it can be better to change linked list to double)
*/

static int     my_outc(int c)
{
    return (write (STDIN_FILENO, &c, 1));
}

int ft_terminal_get_cmd(char **command, t_env **copy_env)
{	
    int ret;
	int size;
	t_list *head;
	t_list *node;
	char *join;

	head = ft_lstnew(0, 0);
	size = 0;
	while (42)
	{
		ret = ft_terminal_read_key();
		if (ret == KEY_TERM_ENTER)
			break ;
		if (ret == KEY_TERM_CTRL_D && size == 0)
		{
			write(0, "exit", 4);
			ret = '\n';
			node = ft_lstnew((void *)"exit", 5);
			ft_lstinsert(&head, node);
			size = 5;
			break ;
		}
		if (ret == KEY_TERM_CTRL_C)
		{
			write(0, "^C", 2);
			ret = '\n';
			node = ft_lstnew((void *)&ret, sizeof(ret));
			ft_lstinsert(&head, node);
			size++;
			ft_putstr_fd("\n", 0);
			ft_terminal_prompt();
		}
		if (ft_isprint(ret) || ret == KEY_TERM_DEL)
		{
			write(0, &ret, sizeof(int));
			node = ft_lstnew((void *)&ret, sizeof(ret));
			ft_lstinsert(&head, node);
			size++;
		}
		if (ret == KEY_TERM_TAB)
		{
			char *complete;
			char *cmd;

			join = ft_node_join(head, size);
			cmd = ft_strrchr(join, ';');
			if (cmd == NULL)
				cmd = join;
			else
				cmd = cmd + 1;
			complete = ft_env_autocomplete_cmd(cmd, copy_env);
			if (complete)
			{
				write(0, complete, ft_strlen(complete));
				node = ft_lstnew((void *)complete, ft_strlen(complete));
				ft_lstinsert(&head, node);
				size += ft_strlen(complete);
				ft_memdel((void **)&complete);
			}
			ft_memdel((void **)&join);
		}
		if (ret == KEY_TERM_DEL)
		{
			join = ft_node_join(head, size);
			ft_terminal_prompt();
			tputs(tgetstr("ce", NULL), 1, my_outc);
			ft_putstr_fd(join, 0);
			ft_memdel((void **)&join);
		}
	}
	ft_putstr_fd("\n\r", STDIN_FILENO);
	join = ft_node_join(head, size);
	*command = ft_strrchr(join, '\n');
	if (*command == NULL)
		*command = ft_strdup(join);
	else
		*command = ft_strdup(*command + 1);
	ft_memdel((void **)&join);
	ft_lstfree(head);
    return (ret);
}