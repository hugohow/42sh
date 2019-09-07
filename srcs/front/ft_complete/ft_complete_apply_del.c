/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_apply_del.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:16:52 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 15:03:58 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_complete_apply_del(t_cmd *cmd)
{
	if (!cmd->context->cursor)
		return (0);
	cmd->len -= 1;
	if (cmd->len < 0)
		cmd->len = 0;
	ft_complete_print_line(cmd);
	cmd->context->cursor--;
	return (0);
}
