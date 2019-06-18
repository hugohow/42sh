/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmp_prefix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:47:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/18 14:55:02 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_env_cmp_prefix(char *prefix, char *line)
{
	int i;

	i = 0;
	while (prefix[i] && line[i] && ft_toupper(prefix[i]) == ft_toupper(line[i]))
		i++;
	if (prefix[i] == 0 && line[i] == '=')
		return (0);
	return (1);
}
