/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:25:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/19 22:34:43 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_get_args(char *cmd, t_env **copy_env)
{
	char	**args;
	int		i;

	args = ft_strsplit(cmd, ' ');
	i = 0;	
	while (args[i])
	{
		args[i] = ft_get_args_dollar(args[i], copy_env);
		if (args[i] == NULL)
			break;
		args[i] = ft_get_args_tilde(args[i], copy_env);
		// while (ft_strchr(args[i], '~'))
		// 	args[i] = ft_replace_tilde(args[i]);
		i++;
	}
	return (args);
}