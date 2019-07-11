/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_get_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:08:21 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 22:18:53 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*ft_args_get_first(char *cmd, t_env **copy_env)
{
	char	*cmd_exec;
	char	*tmp;
	char	*to_free;
	int		res_parse;

	res_parse = 0;
	if (ft_str_brackets_is_valid(cmd, ft_strlen(cmd)) == 0)
	{
		ft_dprintf(2, \
			"minishell: syntax error: unexpected end of file\n");
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = 2;
		*((int *)ft_vars_get_value(KEY_MUST_EXIT)) = 1;
		return (NULL);
	}
	cmd_exec = ft_cmd_exec_get(cmd);
	if (cmd_exec == NULL)
		return (NULL);
	cmd_exec = ft_args_tilde_get(cmd_exec, copy_env);
	cmd_exec = ft_strtrim_free(cmd_exec);
	tmp = ft_args_dollar_get(cmd_exec, copy_env, &res_parse);
	if (tmp == NULL)
	{
		ft_memdel((void **)&(cmd_exec));
		return (NULL);
	}
	to_free = cmd_exec;
	cmd_exec = tmp;
	ft_memdel((void **)&to_free);
	return (cmd_exec);
}
