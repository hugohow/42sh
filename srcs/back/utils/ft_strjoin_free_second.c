/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_second.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:19:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 18:03:55 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strjoin_free_second(char *prefix, char *to_free)
{
	char	*new_str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (prefix == NULL || to_free == NULL)
		return (NULL);
	len = ft_strlen(prefix) + ft_strlen(to_free) + 1;
	if (!(new_str = (char *)ft_memalloc(len * sizeof(char))))
		return (NULL);
	i = -1;
	while (prefix[++i])
		new_str[i] = prefix[i];
	j = -1;
	while (to_free[++j])
		new_str[i++] = to_free[j];
	new_str[i] = '\0';
	ft_memdel((void **)&to_free);
	return (new_str);
}
