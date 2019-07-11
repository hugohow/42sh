/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_dollar_get.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:42:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 12:45:44 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_args_dollar_get(char *str, t_env **copy_env, int *p_result_parsing)
{
	int		i;
	int		ret;
	char	*output;
	char	*to_free;

	i = 0;
	if (str == NULL)
		return (NULL);
	output = ft_strdup(str);
	while (output && output[i])
	{
		if (output[i] == '$')
		{
			if (((ret = ft_args_dollar_is_valid(output + i))) == -1)
			{
				*p_result_parsing = 1;
				ft_putstr_fd("minishell: Bad substitution\n", 2);
				ft_memdel((void **)&output);
				return (NULL);
			}
			to_free = output;
			output = ft_args_dollar_replace_expansion(output, i, ret, copy_env);
			ft_memdel((void **)&to_free);
		}
		i++;
	}
	return (output);
}
