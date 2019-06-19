/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_tilde.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:46:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/19 22:10:09 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_get_args_tilde(char *str, t_env **copy_env)
{
	char *line;
	int i;


	i = 0;
	while (str[i])
	{
		// je ne comprends pas poutquoi y'a pas ':' comme indiqué dans la doc
		if (str[i] == '~' && (i == 0 || str[i - 1] == '='))
		{
			if (str[i + 1] == '~')
			{
				i++;
			}
			else if (str[i + 1] == 0 || str[i + 1] == '/')
			{
				line = ft_env_get_value(copy_env, "HOME");
				if (line)
				{
					str[i] = 0;
					if (str[i + 1] == '/')
						line = ft_strjoin(line, str + i + 1);
					str = ft_strjoin(str, line);
					return (ft_get_args_tilde(str, copy_env));
				}
			}
			else if (str[i + 1] == '-' && (str[i + 2] == 0 || str[i + 2] == '/'))
			{
				line = ft_env_get_value(copy_env, "OLDPWD");
				if (line)
				{
					str[i] = 0;
					str[i + 1] = 0;
					if (str[i + 2] == '/')
						line = ft_strjoin(line, str + i + 2);
					line = ft_strjoin(line, str + i + 1);
					str = ft_strjoin(str, line);
					return (ft_get_args_tilde(str, copy_env));
				}
			}
			else if (str[i + 1] == '+' && (str[i + 2] == 0 || str[i + 2] == '/'))
			{
				line = ft_env_get_value(copy_env, "PWD");
				if (line)
				{
					str[i] = 0;
					str[i + 1] = 0;
					if (str[i + 2] == '/')
						line = ft_strjoin(line, str + i + 2);
					str = ft_strjoin(str, line);
					return (ft_get_args_tilde(str, copy_env));
				}
			}
		}
		i++;
	}


	return (str);
}