/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_ctrl_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 03:03:27 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 14:10:15 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_apply_ctrl_c(t_cmd *cmd)
{
	t_vars	*p_vars;

	(void)cmd;
	p_vars = ft_vars_get();
	if (p_vars->cmd)
	{
		ft_lstfree((p_vars->cmd)->head);
		ft_memdel((void **)&(p_vars->cmd));
	}
	if ((ft_cmd_init()) < 0)
		return (0);
	ft_putstr_fd("^C\n", 0);
	ft_interactive_prompt();
	return (1);
}
