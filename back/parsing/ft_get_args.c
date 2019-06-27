/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:25:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 16:27:57 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_get_args(char *cmd, t_env **copy_env, int *p_result_parsing)
{
	char	**args;
	int		i;

	args = ft_strsplit(cmd, ' ');
	i = 0;	
	while (args && args[i])
	{
		args[i] = ft_get_args_dollar(args[i], copy_env, p_result_parsing);
		if (args[i] == NULL)
			return (NULL);
		args[i] = ft_get_args_tilde(args[i], copy_env);
		args[i] = ft_strtrim(args[i]);
		i++;
	}
	return (args);
}