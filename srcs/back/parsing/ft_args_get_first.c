/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_get_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:08:21 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 17:15:58 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_cmd_exec(char *cmd)
{
	char	*output;
	int		i;
	int		j;

	if (!(output = (char *)ft_memalloc((ft_strlen(cmd) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i] && (cmd[i] == '\t' || cmd[i] == '\v' || cmd[i] == '\f' || \
		cmd[i] == '\r' || cmd[i] == '\n' || cmd[i] == ' ' || cmd[i] == ';'))
		i++;
	while (cmd[i] && !(cmd[i] == '\t' || cmd[i] == '\v' || cmd[i] == '\f' || \
		cmd[i] == '\r' || cmd[i] == '\n' || cmd[i] == ' ' || cmd[i] == ';'))
	{
		output[j] = ft_tolower(cmd[i]);
		j++;
		i++;
	}
	output[j] = 0;
	if (j == 0)
		ft_memdel((void **)&output);
	return (output);
}

char		*ft_args_get_first(char *cmd, t_env **copy_env)
{
	char	*cmd_exec;
	char	*tmp;
	char	*to_free;
	int		res_parse;

	res_parse = 0;
	cmd_exec = get_cmd_exec(cmd);
	if (cmd_exec == NULL)
		return (NULL);
	cmd_exec = ft_strtrim_free(cmd_exec);
	cmd_exec = ft_args_tilde_get(cmd_exec, copy_env);
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
