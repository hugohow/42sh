/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_get_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 13:57:41 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read one line of stdin (it can be better to change linked list to double)
*/

static int	ft_cmd_init(void)
{
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	p_vars->cmd = (t_cmd *)ft_memalloc(sizeof(t_cmd));
	if ((p_vars->cmd) == NULL)
		return (-1);
	(p_vars->cmd)->head = ft_lstnew(0, 0);
	(p_vars->cmd)->size = 0;
	(p_vars->cmd)->len = 0;
	(p_vars->cmd)->last_key = 0;
	return (0);
}

static void		free_and_assign(char **command)
{
	char *join;
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	join = ft_node_join((p_vars->cmd)->head, (p_vars->cmd)->size);
	*command = ft_strrchr(join, '\n');
	if (*command == NULL)
		*command = ft_strdup(join);
	else
		*command = ft_strdup(ft_strrchr(join, '\n') + 1);
	ft_memdel((void **)&join);
	ft_lstfree((p_vars->cmd)->head);
	ft_memdel((void **)&(p_vars->cmd));
}

int				ft_interactive_get_cmd(char **command)
{
	int		ret;
	t_vars	*p_vars;

	if ((ft_cmd_init()) < 0)
		return (0);
	p_vars = ft_vars_get();
	while (42)
	{
		ret = ft_interactive_read_key();
		(p_vars->cmd)->last_key = ret;
		*((int *)ft_vars_get_value(KEY_LAST_KEY)) = (int)ret;
		ret = ft_apply_key((p_vars->cmd));
		if (ret == 0)
			break ;
	}
	ft_putstr_fd("\n\r", STDIN_FILENO);
	free_and_assign(command);
	return (ret);
}
