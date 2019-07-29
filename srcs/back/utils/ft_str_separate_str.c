/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_separate_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:17:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/29 18:26:21 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		begin_with(const char *str, const char *begin)
{
	int i;

	i = 0;
	if (str == NULL || begin == NULL)
		return (0);
	while (str[i] && begin[i] && str[i] == begin[i])
		i++;
	if (begin[i] == 0)
		return (1);
	return (0);
}

static char		*get_word(const char *str, char const *to_separate)
{
	char		*word;
	size_t		j;

	if (!(word = (char *)ft_memalloc((ft_strlen(str) + 1) * sizeof(*word))))
		return (NULL);
	j = 0;
	while (str[j] && begin_with(str + j, to_separate) == 0)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char		**fill_list_init(char const *str, char const *to_separate)
{
	size_t	k;
	char	**list;

	if (str == NULL)
		return (NULL);
	if (!(list = (char **)ft_memalloc((ft_strlen(str) * 4 + 3)\
		* sizeof(char *))))
		return (NULL);
	k = 0;
	if (ft_strlen(str) == 0)
	{
		list[k++] = ft_strdup("");
		list[k++] = 0;
		return (list);
	}
	if (begin_with(str, to_separate) == 1)
	{
		list[k++] = ft_strdup("");
		if (str[ft_strlen(to_separate)] == 0)
			list[k++] = ft_strdup("");
	}
	return (list);
}

char			**ft_str_separate_str(char const *str, char const *to_separate)
{
	char		**list;
	int			i;
	size_t		k;

	if (!(list = fill_list_init(str, to_separate)))
		return (NULL);
	k = 0;
	while (list[k])
		k++;
	i = 0;
	while (str[i])
	{
		if (begin_with(str + i, to_separate) == 0)
		{
			list[k++] = get_word(str + i, to_separate);
			i += ft_strlen(list[k - 1]);
			continue ;
			if (str[i] == 0)
				break ;
		}
		else if (str[i + ft_strlen(to_separate)] && begin_with(str + i + ft_strlen(to_separate), to_separate) == 1)
		{
			list[k++] = strdup("");
		}
		i += ft_strlen(to_separate);
		if (str[i] == 0)
			list[k++] = ft_strdup("");
	}
	list[k++] = 0;
	return (list);
}
