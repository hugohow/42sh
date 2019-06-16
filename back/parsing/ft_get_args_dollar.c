/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:42:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 13:55:53 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	ft_is_special_char(char c)
{
	if (c == '*' || c == '@' || c == '#' || c == '?'|| c == '-' || c == '$' || c == '!' || c == '0'|| c == '_')
		return (1);
	return (0);
}

char *ft_get_args_dollar(char *str, t_env **copy_env)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			size_t len;

			len = 0;
			i++;
			if (ft_is_special_char(str[i]))
			{

			}
			else
			{
				while (str[i + len] && str[i + len] != '/' && ft_isalnum(str[i + len]))
					len++;
				if (len != 0)
				{
					// str[i - 1] = ' ';
					char *line;

					line = ft_get_line_env_n(copy_env, str + i, len);
					if (line)
					{
						char *tmp;
						str[i - 1] = 0;
						tmp = ft_strjoin(str, line + len + 1);
						str = ft_strjoin(tmp, str + i + len);
					}
					else if (len == 1)
					{
						printf("parmam : %c\n", str[i]);
					}
					else
					{
						str[i - 1] = 0;
						str = ft_strjoin(str, str + i + len);
					}
					i += len - 1;
				}
				else
				{
				
				}
			}
		}
		i++;
	}
	return (str);
}