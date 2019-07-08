/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 03:25:09 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 20:52:16 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const	t_fts_apply g_fcts[] =
{
	{KEY_TERM_ENTER, &ft_apply_enter},
	{KEY_TERM_CTRL_C, &ft_apply_ctrl_c},
	{KEY_TERM_CTRL_D, &ft_apply_ctrl_d},
	{KEY_TERM_TAB, &ft_apply_tab},
	{KEY_TERM_DEL, &ft_apply_del},
	{0, &ft_apply_printable},
};

int				ft_apply_key(t_cmd *cmd)
{
	int			i;
	t_ft_apply	*ft;

	i = 0;
	while (g_fcts[i].key)
	{
		if (g_fcts[i].key == cmd->last_key)
		{
			ft = g_fcts[i].fct;
			return (ft(cmd));
		}
		i++;
	}
	ft = g_fcts[i].fct;
	return (ft(cmd));
}
