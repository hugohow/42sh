/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:37:25 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 16:15:50 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_escapable_fttrim(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int	count_len_fttrim(const char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] && is_escapable_fttrim(str[i]))
		i++;
	while (str[i])
	{
		i++;
		len++;
	}
	i--;
	while (i >= 0 && str[i] && is_escapable_fttrim(str[i]))
	{
		i--;
		len--;
	}
	return (len);
}

char		*ft_strtrim_free(char *str)
{
	char	*output;
	int		i;
	int		k;
	int		len;

	if (str == NULL)
		return (NULL);
	len = count_len_fttrim(str);
	if (len <= 0)
	{
		ft_memdel((void **)&str);
		return (ft_strdup(""));
	}
	if (!(output = (char *)ft_memalloc((len + 1) * sizeof(char))))
	{
		ft_memdel((void **)&str);
		return (NULL);
	}
	i = 0;
	k = -1;
	while (str[i] && is_escapable_fttrim(str[i]))
		i++;
	while (++k < len)
		output[k] = str[i++];
	output[k] = '\0';
	ft_memdel((void **)&str);
	return (output);
}
