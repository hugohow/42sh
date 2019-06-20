/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_get_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 22:08:25 by hhow-cho         ###   ########.fr       */
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

static char *join_nodes(t_list *head, int size)
{
	char *output;
	t_list *node;

	if (!(output = (char *)ft_memalloc((size + 1) * sizeof(char))))
		return (NULL);
	node = head;
	while (node)
	{
		if (node->content)
			output = ft_strcat(output, (char *)(node->content));
		node = node->next;
	}
	while (ft_strchr(output, 127))
	{
		int i;
		int j;

		i = 0;
		while (output[i])
		{
			if (output[i] == 127 && i > 0)
			{
				j = i - 1;
				while (output[j + 2])
				{
					output[j] = output[j + 2];
					j++;
				}
				output[j] = 0;
				break ;
			}
			else if (output[i] == 127 && i == 0)
			{
				j = i + 1;
				while (output[j])
				{
					output[j - 1] = output[j];
					j++;
				}
				output[j - 1] = 0;
			}
			i++;
		}
	}
	return (output);
}

int ft_terminal_get_cmd(char **command, t_env **copy_env)
{	
    int ret;
	int size;
	t_list *head;
	t_list *node;

	head = ft_lstnew(0, 0);
	size = 0;
	while (42)
	{
		ret = ft_terminal_read_key();
		if (ret == 10)
			break ;
		if (ft_isprint(ret) || ret == 127)
		{
			write(0, &ret, sizeof(int));
			node = ft_lstnew((void *)&ret, sizeof(ret));
			ft_lstinsert(&head, node);
			size++;
		}
		if (ret == 9)
		{
			char *complete;
			char *cmd;

			cmd = ft_strrchr(join_nodes(head, size), ';');
			if (cmd == NULL)
				cmd = join_nodes(head, size);
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
		}
		if (ret == 127)
		{
			// node = ft_lstnew((void *)&ret, sizeof(ret));
			// ft_lstinsert(&head, node);
			// size++;

			ft_putstr_fd("\r", 0);
			ft_putstr_fd(NAME, 0);
			ft_putstr_fd(ft_strrchr(getcwd(NULL, 0), '/') + 1, 0);
			ft_putstr_fd(PROMPT, 0);
			tputs(tgetstr("ce", NULL), 1, my_outc);
			ft_putstr_fd(join_nodes(head, size), 0);
		}
	}
	ft_putchar_fd('\n', STDIN_FILENO);
	*command = join_nodes(head, size);
	ft_lstfree(head);
    return (ret);
}