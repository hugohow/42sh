/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_get_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:08:21 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/25 14:22:32 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_error(char *cmd)
{
	if (ft_str_brackets_is_valid(cmd, ft_strlen(cmd)) == 0)
	{
		ft_dprintf(2, \
			"21sh: syntax error: unexpected end of file\n");
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = 2;
		*((int *)ft_vars_get_value(KEY_MUST_EXIT)) = 1;
		return (1);
	}
	return (0);
}

char		*ft_args_get_first(char *cmd, t_env **copy_env)
{
	char	*cmd_exec;
	char	*tmp;
	char	*to_free;
	int		res_parse;

	res_parse = 0;
	if (handle_error(cmd) == 1)
		return (NULL);
	if (!(cmd_exec = ft_cmd_exec_get(cmd)))
		return (NULL);
	cmd_exec = ft_args_tilde_get(cmd_exec, copy_env);
	cmd_exec = ft_strtrim_free(cmd_exec);
	if (!(tmp = ft_args_dollar_get(cmd_exec, copy_env, &res_parse)))
	{
		ft_memdel((void **)&(cmd_exec));
		return (NULL);
	}
	to_free = cmd_exec;
	cmd_exec = tmp;
	ft_memdel((void **)&to_free);
	return (cmd_exec);
}
