/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_autocomplete_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:08:05 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/21 00:06:15 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static const char *ft_get_possibilities(char *begin, t_env **copy_env)
{
	t_ht *table;
	const char *suggestion;
	int i;
	int k;

	i = 0;
	k = 0;
	suggestion = NULL;
    while (copy_env[i])
    {
		if (ft_env_cmp_prefix("PATH", copy_env[i]->line) == 0)
		{
			table = copy_env[i]->table;
			i = 0;
			while (i < (int)table->size)
			{
				t_node_ht *node;

				node = table->list[i];
				while (node)
				{
					if (ft_strncmp(begin, node->key, ft_strlen(begin)) == 0)
					{
						if (suggestion == NULL)
							suggestion = node->key;
						if (ft_strlen(suggestion) > ft_strlen(node->key))
							suggestion = node->key;
						k++;
					}
					node = node->next;
				}
				i++;
			}
			break ;
		}
        i++;
    }
	return (suggestion);
}

char *ft_env_autocomplete_cmd(char *begin, t_env **copy_env)
{
    int i;
	int k;
	const char *suggestion;


    i = 0;
	k = 0;
	k = 0;
	while (*begin == ' ')
		begin++;
	suggestion = ft_get_possibilities(begin, copy_env);
	if (suggestion == NULL)
		return (NULL);
	if (suggestion == NULL)
		return (NULL);
	if (ft_strlen(suggestion) == ft_strlen(begin))
		return (NULL);
    return (ft_strdup(suggestion + ft_strlen(begin)));
}