/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bins_table_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:03:23 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/24 23:03:32 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ht * ft_bins_table_get(t_env **copy_environ)
{
	int i;

	i = 0;
	while (copy_environ[i])
	{
		if (ft_env_cmp_prefix("PATH", copy_environ[i]->line) == 0)
			return (copy_environ[i]->table);
		i++;
	}
	return (NULL);
}