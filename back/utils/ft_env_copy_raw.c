/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_copy_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:12:28 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/23 11:12:47 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

t_env **ft_env_copy_raw(char **str, char **argv)
{
    t_env **copy;
	int path_present;
	int pwd_present;
	int term_present;
    int i;

    i = 0;
    while (str[i])
        i++;
    if (!(copy = (t_env **)ft_memalloc((i + 20) * sizeof(t_env *))))
		return (NULL);
    i = 0;
	path_present = 0;
	pwd_present = 0;
	term_present = 0;
    while (str[i])
    {
        copy[i] = ft_memalloc(sizeof(t_env));
        copy[i]->line = ft_strdup(str[i]);
		if (ft_env_cmp_prefix("PATH", copy[i]->line) == 0)
		{
			path_present = 1;
			copy[i]->table = ft_bins_table_create(copy[i]->line);
		}
		else
			copy[i]->table = NULL;
		if (ft_env_cmp_prefix("PWD", copy[i]->line) == 0)
		{
			pwd_present = 1;
		}
		if (ft_env_cmp_prefix("TERM", copy[i]->line) == 0)
		{
			term_present = 1;
		}

        copy[i]->special = 0;
        i++;
    }
	if (path_present == 0)
	{
        copy[i] = ft_memalloc(sizeof(t_env));
        copy[i]->line = ft_strdup("PATH=/usr/sbin:/usr/bin:/sbin:/bin");
		copy[i]->table = ft_bins_table_create(copy[i]->line);
        copy[i]->special = 0;
        i++;
	}
	if (term_present == 0)
	{
        copy[i] = ft_memalloc(sizeof(t_env));
        copy[i]->line = ft_strdup("TERM=xterm-256color");
        copy[i]->special = 0;
        i++;
	}
	if (pwd_present == 0)
	{
        copy[i] = ft_memalloc(sizeof(t_env));
        copy[i]->line = ft_strjoin("PWD=", getcwd(NULL, 0));
        copy[i]->special = 0;
        i++;
	}
	copy[i] = ft_memalloc(sizeof(t_env));
	copy[i]->line = ft_strjoin("$=", ft_itoa((int)getpid()));
	copy[i]->special = 1;
	i++;


	copy[i] = ft_memalloc(sizeof(t_env));
	copy[i]->line = ft_strdup("?=0");
	copy[i]->special = 1;
	i++;

	copy[i] = ft_memalloc(sizeof(t_env));
	copy[i]->line = ft_strdup("!=");
	copy[i]->special = 1;
	i++;

	int k;

	k = 0;
	while (argv[k])
	{
		copy[i] = ft_memalloc(sizeof(t_env));
		copy[i]->line = ft_strjoin(ft_strjoin(ft_itoa(k), "="), argv[k]);
		copy[i]->special = 1;
		i++;
		k++;
	}

	copy[i] = ft_memalloc(sizeof(t_env));
	copy[i]->line = ft_strjoin("#=", ft_itoa(k - 1));
	copy[i]->special = 1;
	i++;


    copy[i] = 0;
    return (copy);
}
