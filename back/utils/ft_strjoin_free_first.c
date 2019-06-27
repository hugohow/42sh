/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_first.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:18:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 21:22:49 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_strjoin_free_first(char *to_free, char *str)
{
	char	*new_str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (to_free == NULL || str == NULL)
		return (NULL);
	len = ft_strlen(to_free) + ft_strlen(str) + 1;
	if (!(new_str = (char *)ft_memalloc(len * sizeof(char))))
		return (NULL);
	i = -1;
	while (to_free[++i])
		new_str[i] = to_free[i];
	j = -1;
	while (str[++j])
		new_str[i++] = str[j];
	new_str[i] = '\0';
	ft_memdel((void **)&to_free);
	return (new_str);
}