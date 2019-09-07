/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_apply_enter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:32:25 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 18:11:32 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_complete_apply_enter(t_cmd *cmd)
{
	cmd->context->cursor = cmd->context->width;
	tputs(tgetstr("nw", NULL), 1, ft_putchar_stdin);
	ft_complete_add_printable(cmd, '\n');
	tputs(tgetstr("cr", NULL), 1, ft_putchar_stdin);
	ft_putstr_fd("\n", 0);
	ft_putstr_fd(cmd->context->prompt, 0);
	cmd->context->cursor = 0;
	cmd->context->width = 0;
	return (0);
}
