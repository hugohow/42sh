/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:53:32 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/10 12:05:45 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	is_escapable(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || \
		c == '\r' || c == '\n' || c == ' ' || c == ';')
		return (1);
	return (0);
}

static char		*get_word(const char *str)
{
	char		*word;
	size_t		j;

	if (!(word = (char *)ft_memalloc((ft_strlen(str) + 1) * sizeof(char))))
		return (NULL);
	j = 0;
	while (str[j] && is_escapable(str[j]) == 0)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char			**ft_args_split(char *str)
{
	char		**list;
	int			i;
	size_t		k;

	if (str == NULL)
		return (NULL);
	if (!(list = (char **)ft_memalloc((ft_strlen(str) + 1)\
		* sizeof(char *))))
		return (NULL);
	i = -1;
	k = 0;
	while (str[++i])
	{
		if (is_escapable(str[i]) == 0)
		{
			list[k++] = get_word(str + i);
			i += ft_strlen(list[k - 1]) - 1;
		}
	}
	list[k++] = 0;
	return (list);
}


char	*ft_cmd_exec_get(char *cmd)
{
	char	*output;
	int		i;
	int		j;

	if (!(output = (char *)ft_memalloc((ft_strlen(cmd) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i] && (cmd[i] == '\t' || cmd[i] == '\v' || cmd[i] == '\f' || \
		cmd[i] == '\r' || cmd[i] == '\n' || cmd[i] == ' ' || cmd[i] == ';'))
		i++;
	while (cmd[i] && !(cmd[i] == '\t' || cmd[i] == '\v' || cmd[i] == '\f' || \
		cmd[i] == '\r' || cmd[i] == '\n' || cmd[i] == ' ' || cmd[i] == ';'))
	{
		output[j] = ft_tolower(cmd[i]);
		j++;
		i++;
	}
	output[j] = 0;
	if (j == 0)
		ft_memdel((void **)&output);
	return (output);
}