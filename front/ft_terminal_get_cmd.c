/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_get_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 18:02:08 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/*
** Read one line of stdin (it can be better to change linked list to double)
*/

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
	return (output);
}

int ft_terminal_get_cmd(char **command)
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
		if (ret != 9 && ft_isprint(ret))
		{
			write(0, &ret, sizeof(int));
			node = ft_lstnew((void *)&ret, sizeof(ret));
			ft_lstinsert(&head, node);
			size++;
		}
	}
	ft_putchar_fd('\n', STDIN_FILENO);
	*command = join_nodes(head, size);
	ft_lstfree(head);
    return (ret);
}