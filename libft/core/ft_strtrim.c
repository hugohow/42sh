/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:13:02 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 22:17:38 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_escapable_fttrim(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n' || \
		c == '"' || c == 39 || c == ' ')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *str)
{
	char	*output;
	int		i;
	int		k;

	if (str == NULL)
		return (NULL);
	if (!(output = (char *)ft_memalloc((ft_strlen(str) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (is_escapable_fttrim(str[i]) == 0)
		{
			output[k] = str[i];
			k++;
		}
		i++;
	}
	output[k] = '\0';
	if (k == 0)
	{
		ft_memdel((void **)&output);
		return (NULL);
	}
	return (output);
}

char		*ft_strtrim_free(char *str)
{
	char	*output;
	output = ft_strtrim(str);
	ft_memdel((void **)&str);
	return (output);
}
