/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_table_bins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 15:24:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 14:05:56 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ht *ft_create_table_bins(t_env **copy_env)
{
	char **paths;
    char *new_path;
    char *d_name;
	int i;
	t_ht *table_bins;

	table_bins = ft_ht_create();
	paths = get_paths(copy_env);
	i = 0;
    while (paths[i])
    {

		DIR *pDir;
		struct dirent *pDirent;

		if ((pDir = opendir (paths[i])) == NULL)
		{
			break;
		}
		while ((pDirent = readdir(pDir)) != NULL) 
		{
			d_name = pDirent->d_name;
            new_path = ft_strjoin(paths[i], "/");
            new_path = ft_strjoin(new_path, d_name);
			ft_ht_add(table_bins, d_name, (void *)(new_path));
			// printf("%s\n", d_name);
		}
		closedir (pDir);
        i++;
    }

	return (table_bins);
}