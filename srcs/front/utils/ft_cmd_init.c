/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:07:28 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 14:07:49 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_cmd_init(void)
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
