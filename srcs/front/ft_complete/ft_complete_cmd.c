/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:07:32 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/07 15:24:13 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_complete(char *prompt)
{
	int			ret;
	t_context 	context;
	t_cmd		*cmd;
	t_vars		*p_vars;

	p_vars = ft_vars_get();
	cmd = p_vars->cmd;
	memset(&context, '\0', sizeof(t_context));
	cmd->context = &context;
	context.prompt = prompt;
	context.cursor = 0;
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
	if (ft_complete_check(cmd->head, "\""))
		return (ft_complete("dquote> "));
	return (NULL);
}
