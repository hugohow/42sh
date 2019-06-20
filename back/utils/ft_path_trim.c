/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:37:59 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 16:38:07 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_path_trim(char *path)
{
	int i;
	int j;
	char **list;
	char *new_path;

	list = ft_strsplit(path, '/');
	new_path = ft_memalloc((sizeof(char) * (ft_strlen(path) + 1)));
	i = 0;
	while (list[i])
	{
		if (ft_strcmp(list[i], ".") == 0)
		{
			j = i + 1;
			while (list[j])
			{
				list[j - 1] = list[j];
				j++;
			}
			list[j - 1] = 0;
		}
		else if (ft_strcmp(list[i], "..") == 0)
		{
			if (i > 0)
			{
				j = i + 1;
				while (list[j])
				{
					list[j - 2] = list[j];
					j++;
				}
				list[j - 2] = 0;
				i--;
			}
			else
			{
				j = i + 1;
				while (list[j])
				{
					list[j - 1] = list[j];
					j++;
				}
				list[j - 1] = 0;
			}
		}
		else
			i++;
	}
	i = 0;
	ft_strcat(new_path, "/");
	while (list[i])
	{
		ft_strcat(new_path, list[i]);
		if (list[i + 1] != 0)
			ft_strcat(new_path, "/");
		i++;
	}
	return (new_path);
}