/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bins_table_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 15:24:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/23 00:46:01 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ht *ft_bins_table_create(char *line)
{
	char **paths;
    char *new_path;
    char *d_name;
	int i;
	t_ht *table_bins;
	DIR *pDir;
	struct dirent *pDirent;

	table_bins = ft_ht_create();
	if (line == NULL || ft_strlen(line + 5) == 0)
		paths = ft_strsplit("/usr/sbin:/usr/bin:/sbin:/bin:.", ':');
	else
		paths = ft_strsplit(line + 5, ':');
	i = 0;
    while (paths[i])
    {
		if ((pDir = opendir (paths[i])) == NULL)
		{
			break;
		}
		while ((pDirent = readdir(pDir)) != NULL) 
		{
			printf("%s\n", pDirent->d_name);
			d_name = pDirent->d_name;
            new_path = ft_strjoin(paths[i], "/");
            new_path = ft_strjoin(new_path, d_name);
			ft_ht_add(table_bins, d_name, (void *)(new_path));
		}
		closedir (pDir);
        i++;
    }
	return (table_bins);
}