/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_separate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:00:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 11:53:35 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*get_word(const char *str, char c)
{
	char		*word;
	size_t		j;

	if (!(word = (char *)ft_memalloc((ft_strlen(str) + 1) * sizeof(*word))))
		return (NULL);
	j = 0;
	while (str[j] && str[j] != c)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char		**fill_list_init(char const *str, char c)
{
	size_t	k;
	char	**list;

	if (str == NULL)
		return (NULL);
	if (!(list = (char **)ft_memalloc((ft_strlen(str) * 4 + 3) * sizeof(char *))))
		return (NULL);
	k = 0;
	if (ft_strlen(str) == 0)
	{
		list[k++] = ft_strdup("");
		list[k++] = 0;
		return (list);
	}
	if (str[0] == c)
	{
		list[k++] = ft_strdup("");
		if (str[1] == 0)
			list[k++] = ft_strdup("");
	}
	return (list);
}

char			**ft_str_separate(char const *str, char c)
{
	char		**list;
	char		*word;
	int			i;
	size_t		k;

	list = fill_list_init(str, c);
	if (list == NULL)
		return (NULL);
	k = 0;
	while (list[k])
		k++;
	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
		{
			word = get_word(str + i, c);
			list[k++] = word;
			i += ft_strlen(word) - 1;
		}
		else if (str[i + 1] && str[i + 1] == c)
		{
			list[k++] = strdup("");
		}
	}
	if (i > 1 && str[i - 1] == c)
		list[k++] = ft_strdup("");
	list[k++] = 0;
	return (list);
}
