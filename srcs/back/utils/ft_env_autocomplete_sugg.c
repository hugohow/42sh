/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_autocomplete_sugg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 20:05:46 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 20:35:24 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const	char *builtins[] =
{
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_SETENV,
	BUILTIN_UNSETENV,
	0
};

const char *ft_env_autocomplete_sugg_builtins(char *begin)
{
	int i;
	const char *suggestion;

	i = 0;
	suggestion = NULL;
	while (builtins[i])
	{
		if (ft_strncmp(begin, builtins[i], ft_strlen(begin)) == 0)
		{
			suggestion = builtins[i];
			break ;
		}
		i++;
	}
	return (suggestion);
}

const char *ft_env_autocomplete_sugg_table(char *begin)
{
	int i;
	t_node_ht *node;
	const char *suggestion;
	t_ht **p_table;
	t_ht *table;

	p_table = ft_p_bins_table_get();
	if (p_table == NULL)
		return (NULL);
	table = *p_table;
	if (table == NULL)
		return (NULL);
	i = 0;
	suggestion = NULL;
	while (i < (int)table->size)
	{
		node = table->list[i];
		while (node)
		{
			if (ft_strncmp(begin, node->key, ft_strlen(begin)) == 0)
			{
				if (suggestion == NULL)
					suggestion = node->key;
				if (ft_strlen(suggestion) > ft_strlen(node->key))
					suggestion = node->key;
			}
			node = node->next;
		}
		i++;
	}
	return (suggestion);
}