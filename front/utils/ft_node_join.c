/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:43:40 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/25 00:10:09 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char *apply_del(char *output, int i)
{
	int j;

	if (i > 0)
	{
		j = i - 1;
		while (output[j + 2])
		{
			output[j] = output[j + 2];
			j++;
		}
		output[j] = 0;
		return (output);
	}
	j = i + 1;
	while (output[j])
	{
		output[j - 1] = output[j];
		j++;
	}
	output[j - 1] = 0;	
	return (output);
}

char *ft_node_join(t_list *head, int size)
{
	char *output;
	t_list *node;
	int i;

	if (!(output = (char *)ft_memalloc((size + 1) * sizeof(char))))
		return (NULL);
	node = head;
	while (node)
	{
		if (node->content)
			output = ft_strcat(output, (char *)(node->content));
		node = node->next;
	}
	while (ft_strchr(output, 127))
	{
		i = 0;
		while (output[i])
		{
			if (output[i] == 127)
			{
				output = apply_del(output, i);
				break ;
			}
			i++;
		}
	}
	return (output);
}