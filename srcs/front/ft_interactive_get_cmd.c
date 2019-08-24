/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_get_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 01:12:25 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read one line of stdin (it can be better to change linked list to double)
*/

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
	parse_dquote();
	ft_putstr_fd("\n\r", STDIN_FILENO);
	free_and_assign(command);
	return (ret);
}
