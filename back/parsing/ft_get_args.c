/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:25:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/24 21:27:04 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_get_args(char *cmd, t_env **copy_env, int *p_result_parsing)
{
	char	**args;
	int		i;

	args = ft_strsplit(cmd, ' ');
	i = 0;	
	while (args[i])
	{
		args[i] = ft_get_args_dollar(args[i], copy_env, p_result_parsing);
		if (args[i] == NULL)
			break ;
		args[i] = ft_get_args_tilde(args[i], copy_env);
		i++;
	}
	return (args);
}