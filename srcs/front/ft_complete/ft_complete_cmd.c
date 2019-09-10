/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:07:32 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 18:06:00 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_complete(t_cmd *cmd)
{
	int			ret;

	ft_complete_apply_enter(cmd);
	while (42)
	{
		ret = ft_interactive_read_key();
		if (ret == KEY_TERM_ENTER && cmd->last_key == '"')
			break ;
		cmd->last_key = ret;
		ft_complete_apply_key(cmd);
	}
	return (NULL);
}

char		*ft_complete_cmd(t_cmd *cmd)
{
	t_context	context;

	ft_memset(&context, '\0', sizeof(t_context));
	if (ft_complete_check(cmd->head, "\""))
		context.prompt = "dquote> ";
	if (ft_complete_check(cmd->head, "{}"))
		context.prompt = "cursh> ";
	if (ft_complete_check(cmd->head, "'"))
		context.prompt = "quote> ";
	if (context.prompt)
	{
		cmd->context = &context;
		ft_complete(cmd);
		cmd->context = NULL;
	}
	return (NULL);
}