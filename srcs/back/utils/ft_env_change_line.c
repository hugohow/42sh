/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_change_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:01:20 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 20:54:51 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_env_change_line(char *prefix, char *line, t_env **cpy_environ)
{
    size_t i;
	char *to_free;
	t_vars 	*p_vars;
	
    i = 0;
	if (line == NULL)
		return (1);
	if (prefix == NULL)
		return (1);
    while (cpy_environ[i])
    {
		if (ft_env_cmp_prefix(prefix, cpy_environ[i]->line) == 0)
		{
			to_free = (cpy_environ[i])->line;
			if (ft_env_cmp_prefix("PATH", line) == 0)
			{
				p_vars = ft_vars_get();
				p_vars->hash_table = ft_bins_table_create(line);
			}
			(cpy_environ[i])->line = line;
			ft_memdel((void **)&to_free);
			return (1);
		}
        i++;
    }
    return (0);
}