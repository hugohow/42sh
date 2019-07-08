/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_autocomplete_sugg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 20:05:46 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 17:20:41 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const	char *g_builtins[] =
{
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_SETENV,
	BUILTIN_UNSETENV,
	0
};

const char			*ft_env_autocomplete_sugg_builtins(char *begin)
{
	int			i;
	const char	*suggestion;

	i = 0;
	suggestion = NULL;
	while (g_builtins[i])
	{
		if (ft_strncmp(begin, g_builtins[i], ft_strlen(begin)) == 0)
		{
			suggestion = g_builtins[i];
			break ;
		}
		i++;
	}
	return (suggestion);
}

static const char	*check_in_list(t_node_ht *node, \
	char *begin, const char *sugg)
{
	while (node)
	{
		if (ft_strncmp(begin, node->key, ft_strlen(begin)) == 0)
		{
			if (sugg == NULL || \
				(ft_strlen(sugg) > ft_strlen(node->key)))
				sugg = node->key;
		}
		node = node->next;
	}
	return (sugg);
}

const char			*ft_env_autocomplete_sugg_table(char *begin)
{
	int			i;
	t_node_ht	*node;
	const char	*suggestion;
	t_ht		**p_table;
	t_ht		*table;

	suggestion = NULL;
	if (!(p_table = ft_p_bins_table_get()))
		return (NULL);
	if (!(table = *p_table))
		return (NULL);
	i = -1;
	while (++i < (int)table->size)
	{
		node = table->list[i];
		suggestion = check_in_list(node, begin, suggestion);
	}
	return (suggestion);
}
