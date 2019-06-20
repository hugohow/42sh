/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_autocomplete_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:08:05 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 19:26:55 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"


char *ft_env_autocomplete_cmd(char *begin, t_env **copy_env)
{
    int i;
	int k;
	char **suggestions;
	int k_min;

    i = 0;
	k = 0;
	suggestions = (char **)ft_memalloc((9999) * sizeof(char *));
    while (copy_env[i])
    {
		if (ft_env_cmp_prefix("PATH", copy_env[i]->line) == 0)
		{
			t_ht *table;

			table = copy_env[i]->table;
			int i;
			i = 0;
			while (i < (int)table->size)
			{
				t_node_ht *node;

				node = table->list[i];
				while (node)
				{
					if (ft_strncmp(begin, node->key, ft_strlen(begin)) == 0)
					{
						suggestions[k] = ft_strdup(node->key);
						k++;
					}
					node = node->next;
				}
				i++;
			}
		}
        i++;
    }
	suggestions[k] = 0;
	k = 0;
	k_min = 0;
	while (suggestions[k])
	{
		if (ft_strlen(suggestions[k_min]) > ft_strlen(suggestions[k]))
			k_min = k;
		k++;
	}
	if (suggestions[k_min] == NULL)
		return (NULL);
	// printf("\n%s\n", suggestions[k_min]);
    return (ft_strdup(suggestions[k_min] + ft_strlen(begin)));
}