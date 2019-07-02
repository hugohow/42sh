/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 21:17:08 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/01 21:18:46 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_strjoin_(char *str1, char *str2, char *str3)
{
	char	*new_str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (str1 == NULL || str2 == NULL || str3 == NULL)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	if (!(new_str = (char *)ft_memalloc(len * sizeof(char))))
		return (NULL);
	i = -1;
	while (str1[++i])
		new_str[i] = str1[i];
	j = -1;
	while (str2[++j])
		new_str[i++] = str2[j];
	j = -1;
	while (str3[++j])
		new_str[i++] = str3[j];
	new_str[i] = '\0';
	return (new_str);
}