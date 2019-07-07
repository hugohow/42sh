/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_dollar_get.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:42:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 21:50:42 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


char *ft_args_dollar_get(char *str, t_env **copy_env, int *p_result_parsing)
{
	int i;
	int ret;
	char *output;
	char *to_free;

	i = 0;
	output = ft_strdup(str);
	// ft_dprintf(2, "to replace : %s\n", str);
	while (output[i])
	{
		if (output[i] == '$')
		{
			ret = ft_args_dollar_is_valid(output + i);
			if (ret == -1)
			{
				*p_result_parsing = 1;
				ft_putstr_fd("minishell: Bad substitution\n", 2);
				if (output)
					ft_memdel((void **)&output);
				return (NULL);
			}
			if (ret != 0)
			{
				to_free = output;
				output = ft_args_dollar_replace_expansion(output, i, ret, copy_env);
				ft_memdel((void **)&to_free);
			}
		}
		i++;
	}
	return (output);
}