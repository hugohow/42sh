/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_non_interactive_get_cmd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:36:32 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 14:00:29 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read one line of stdin (it can be better to change linked list to double)
*/

static int		ft_cmd_init(void)
{
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	p_vars->cmd = (t_cmd *)ft_memalloc(sizeof(t_cmd));
	if (p_vars->cmd == NULL)
		return (-1);
	(p_vars->cmd)->head = ft_lstnew(0, 0);
	(p_vars->cmd)->size = 0;
	(p_vars->cmd)->len = 0;
	(p_vars->cmd)->last_key = 0;
	return (0);
}

static void		free_and_assign(char **command)
{
	char	*join;
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	join = ft_node_join((p_vars->cmd)->head, (p_vars->cmd)->size);
	*command = join;
	ft_lstfree((p_vars->cmd)->head);
	ft_memdel((void **)&(p_vars->cmd));
}

int				ft_non_interactive_get_cmd(int fd, char **command)
{
	char	ret;
	t_list	*head;
	t_list	*node;
	t_vars	*p_vars;

	if ((ft_cmd_init()) < 0)
		return (0);
	p_vars = ft_vars_get();
	head = (p_vars->cmd)->head;
	while (42)
	{
		if ((read(fd, &ret, sizeof(char)) == 0))
		{
			*((int *)ft_vars_get_value(KEY_MUST_EXIT)) = 1;
			break ;
		}
		(p_vars->cmd)->last_key = (int)ret;
		*((int *)ft_vars_get_value(KEY_LAST_KEY)) = (int)ret;
		if (ret == '\n' || ret == '\0' || ft_isascii((int)ret) == 0)
			break ;
		node = ft_lstnew((void *)&((p_vars->cmd)->last_key), sizeof(int));
		ft_lstinsert(&head, node);
		(p_vars->cmd)->size = (p_vars->cmd)->size + 1;
		(p_vars->cmd)->len = (p_vars->cmd)->len + 1;
	}
	free_and_assign(command);
	return (ret);
}
