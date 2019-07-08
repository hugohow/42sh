/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bins_table_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 15:24:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 16:58:08 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	fill_table(char **paths, t_ht *table_bins)
{
	int				i;
	DIR				*p_dir;
	struct dirent	*p_dirent;
	char			*new_path;

	i = 0;
	while (paths[i])
	{
		if ((p_dir = opendir(paths[i])))
		{
			while ((p_dirent = readdir(p_dir)) != NULL)
			{
				new_path = ft_strjoin_(paths[i], "/", p_dirent->d_name);
				ft_ht_add(table_bins, p_dirent->d_name, (void *)(new_path));
				ft_memdel((void **)&new_path);
			}
			closedir(p_dir);
		}
		i++;
	}
}

t_ht		*ft_bins_table_create(char *line)
{
	char **paths;
	t_ht *table_bins;

	if (!(table_bins = ft_ht_create()))
		return (NULL);
	if (line == NULL || ft_strlen(line) <= 5)
		return (table_bins);
	paths = ft_str_separate(line + 5, ':');
	if (paths == NULL)
	{
		ft_ht_free(&table_bins);
		return (NULL);
	}
	fill_table(paths, table_bins);
	ft_list_free(&paths);
	return (table_bins);
}
