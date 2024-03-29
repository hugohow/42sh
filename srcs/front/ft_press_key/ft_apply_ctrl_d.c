/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_ctrl_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 03:18:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 14:14:01 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_apply_ctrl_d(t_cmd *cmd)
{
	if (cmd->len == 0)
	{
		write(0, "exit", 4);
		*((int *)ft_vars_get_value(KEY_MUST_EXIT)) = 1;
		return (0);
	}
	return (1);
}
