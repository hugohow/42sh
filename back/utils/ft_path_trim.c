/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:37:59 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 02:14:05 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char **shift_left_one(char **list, int i)
{
	int j;

	j = i + 1;
	if (j - 1 >= 0)
	{
		ft_memdel((void **)(&(list[j - 1])));
		while (list[j])
		{
			list[j - 1] = list[j];
			j++;
		}
		list[j - 1] = 0;
	}
	return (list);
}

static char **shift_left_two(char **list, int i)
{
	int j;

	j = i + 1;
	if (j - 2 >= 0)
	{
		ft_memdel((void **)(&(list[j - 1])));
		ft_memdel((void **)(&(list[j - 2])));
		while (list[j])
		{
			list[j - 2] = list[j];
			j++;
		}
		list[j - 2] = 0;
	}
	return (list);
}

static char **clean_list(char **list)
{
	int i;

	i = 0;
	while (list && list[i])
	{
		if (ft_strcmp(list[i], ".") == 0)
		{
			list = shift_left_one(list, i);
			return (clean_list(list));
		}
		else if (ft_strcmp(list[i], "..") == 0)
		{
			if (i > 0)
				list = shift_left_two(list, i);
			else
				list = shift_left_one(list, i);
			return (clean_list(list));
		}
		else
			i++;
	}
	return (list);
}

static void get_new_path(char *new_path, char **list)
{
	int i;

	i = 0;
	while (list && list[i])
	{
		ft_strcat(new_path, list[i]);
		if (list[i + 1] != 0 && new_path[ft_strlen(new_path) - 1] != '/')
			ft_strcat(new_path, "/");
		i++;
	}
	if (new_path[ft_strlen(new_path) - 1] == '/' && ft_strlen(new_path) != 1)
		new_path[ft_strlen(new_path) - 1] = 0;
}


char *ft_path_trim(char *abs_path)
{
	char **list;
	char *new_path;
	size_t len;

	list = ft_str_separate(abs_path, '/');
	len = ft_list_size(list);
	if (list == NULL)
		return (abs_path);
	if (!(new_path = ft_memalloc(sizeof(char) * (ft_strlen(abs_path) + 1))))
	{
		ft_list_free(&list);
		return (NULL);
	}
	if (ft_strcmp(list[0], "") == 0)
		ft_strcat(new_path, "/");
	list = clean_list(list);
	get_new_path(new_path, list);
	ft_list_free(&list);
	return (new_path);
}

char *ft_path_trim_free(char *abs_path)
{
	char **list;
	char *new_path;
	size_t len;

	list = ft_str_separate(abs_path, '/');
	len = ft_list_size(list);
	if (list == NULL)
		return (abs_path);
	if (!(new_path = ft_memalloc(sizeof(char) * (ft_strlen(abs_path) + 1))))
	{
		ft_list_free(&list);
		return (NULL);
	}
	if (ft_strcmp(list[0], "") == 0)
		ft_strcat(new_path, "/");
	list = clean_list(list);
	get_new_path(new_path, list);
	ft_memdel((void **)&abs_path);
	ft_list_free(&list);
	return (new_path);
}