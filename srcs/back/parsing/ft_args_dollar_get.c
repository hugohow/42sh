/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_dollar_get.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:42:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/05 19:40:07 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


char *ft_args_dollar_get(char *str, t_env **copy_env, int *p_result_parsing)
{
	int i;
	int ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ret = ft_args_dollar_is_valid(str + i);
			if (ret == -1)
			{
				*p_result_parsing = 1;
				ft_memdel((void **)&str);
				return (NULL);
			}
			if (ret != 0)
				str = ft_args_dollar_replace_expansion(str, i, ret, copy_env);
		}
		i++;
	}
	if (ft_strlen(str) == 0)
	{
		ft_memdel((void **)&str);
		return (ft_strdup(""));
	}
	return (str);
}