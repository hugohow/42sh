/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bins_table_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 15:24:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 18:52:15 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ht *ft_bins_table_create(char *line)
{
	char **paths;
    char *new_path;
	char *tmp;
    char *d_name;
	int i;
	t_ht *table_bins;
	DIR *pDir;
	struct dirent *pDirent;

	if (!(table_bins = ft_ht_create()))
		return (NULL);
	if (line == NULL)
		paths = ft_strsplit("/usr/sbin:/usr/bin:/sbin:/bin:.", ':');
	else
		paths = ft_strsplit(line + 5, ':');
	if (paths == NULL)
	{
		ft_ht_free(&table_bins);
		return (NULL);
	}
	i = 0;
    while (paths[i])
    {
		if ((pDir = opendir (paths[i])))
		{
			while ((pDirent = readdir(pDir)) != NULL) 
			{
				d_name = pDirent->d_name;
				tmp = ft_strjoin(paths[i], "/");
				new_path = ft_strjoin(tmp, d_name);
				ft_ht_add(table_bins, d_name, (void *)(new_path));
				ft_memdel((void **)&tmp);
				ft_memdel((void **)&new_path);
			}
			closedir (pDir);
		}
        i++;
    }
	ft_list_free(&paths);
	return (table_bins);
}