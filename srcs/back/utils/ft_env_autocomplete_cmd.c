/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_autocomplete_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:08:05 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 20:11:44 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"


static const char *ft_get_possibilities(char *begin, t_env **copy_env)
{
	t_ht *table;
	const char *suggestion;

	suggestion = NULL;
	table = ft_bins_table_get(copy_env);
	suggestion = ft_env_autocomplete_sugg_builtins(begin);
	if (suggestion == NULL)
		suggestion = ft_env_autocomplete_sugg_table(table, begin);
	return (suggestion);
}

char *ft_env_autocomplete_cmd(char *begin, t_env **copy_env)
{
	const char *suggestion;

	while (*begin == ' ')
		begin++;
	suggestion = ft_get_possibilities(begin, copy_env);
	if (suggestion == NULL)
		return (NULL);
	if (ft_strlen(suggestion) == ft_strlen(begin))
		return (NULL);
    return (ft_strdup(suggestion + ft_strlen(begin)));
}