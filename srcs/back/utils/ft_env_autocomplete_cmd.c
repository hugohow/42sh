/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_autocomplete_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:04:51 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 17:09:37 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const char	*ft_get_possibilities(char *begin)
{
	const char *suggestion;

	suggestion = NULL;
	suggestion = ft_env_autocomplete_sugg_builtins(begin);
	if (suggestion == NULL)
		suggestion = ft_env_autocomplete_sugg_table(begin);
	return (suggestion);
}

char				*ft_env_autocomplete_cmd(char *begin, t_env **copy_env)
{
	const char *suggestion;

	(void)copy_env;
	while (*begin == ' ')
		begin++;
	suggestion = ft_get_possibilities(begin);
	if (suggestion == NULL)
		return (NULL);
	if (ft_strlen(suggestion) == ft_strlen(begin))
		return (NULL);
	return (ft_strdup(suggestion + ft_strlen(begin)));
}
