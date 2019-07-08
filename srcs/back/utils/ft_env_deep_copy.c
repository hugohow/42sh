/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_deep_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:27:03 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 17:27:53 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	**ft_env_deep_copy(t_env **cp_env)
{
	t_env	**copy;
	int		i;

	i = 0;
	while (cp_env[i])
		i++;
	if (!(copy = (t_env **)ft_memalloc((i + 1) * sizeof(t_env *))))
		return (NULL);
	i = 0;
	while (cp_env[i])
	{
		if (!(copy[i] = (t_env *)ft_memalloc(sizeof(t_env))))
		{
			ft_env_free(&copy);
			return (NULL);
		}
		copy[i]->line = ft_strdup(cp_env[i]->line);
		i++;
	}
	copy[i] = 0;
	return (copy);
}
