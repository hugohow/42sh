/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_copy_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:12:28 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 21:29:53 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static t_env **exit_env(t_env **env)
{
	ft_putstr_fd(FAIL_COPY_ENV, STDERR_FILENO);
	ft_env_free(&env);
	return (NULL);
}



t_env **ft_env_copy_raw(char **str, char **argv)
{
    t_env **copy;
	int path_present;
	int pwd_present;
	int shlvl_present;
    int i;
	t_vars 	*p_vars;

	p_vars = ft_vars_get();
	
    i = 0;
    while (str[i])
        i++;
    if (!(copy = (t_env **)ft_memalloc((i + 20 + ft_list_size(argv)) * sizeof(t_env *))))
		return (NULL);
    i = 0;
	path_present = 0;
	pwd_present = 0;
	shlvl_present = 0;
	i = 0;
    while (str[i])
    {
        if (!(copy[i] = ft_memalloc(sizeof(t_env))))
			return (exit_env(copy));
		if (ft_env_cmp_prefix("SHLVL", str[i]) == 0)
		{
			int nb;

			nb = ft_atoi((str[i]) + 6) + 1;
			if (nb < 0)
				nb = 0;
			else if (nb >= 1000)
			{
				ft_dprintf(STDERR_FILENO, "shell: shell level (%d) too high, resetting to 1\n", nb);
				nb = 1;
			}
			copy[i]->line = ft_strjoin_free_second("SHLVL=", ft_itoa(nb));
			shlvl_present = 1;
		}
		else
	        copy[i]->line = ft_strdup(str[i]);
		if (ft_env_cmp_prefix("PATH", copy[i]->line) == 0)
		{
			path_present = 1;
			p_vars->hash_table = ft_bins_table_create(copy[i]->line);
		}
		if (ft_env_cmp_prefix("PWD", copy[i]->line) == 0)
		{
			pwd_present = 1;
		}
        i++;
    }
	if (pwd_present == 0)
	{
		char *cwd;

		cwd = (char *)ft_vars_get_value(KEY_CWD);
        if (!(copy[i] = ft_memalloc(sizeof(t_env))))
			return (exit_env(copy));
        copy[i]->line = ft_strjoin("PWD=", cwd);
        i++;
	}
	if (shlvl_present == 0)
	{
        if (!(copy[i] = ft_memalloc(sizeof(t_env))))
			return (exit_env(copy));
		copy[i]->line = ft_strdup("SHLVL=1");
		i++;
	}
	if (path_present == 0)
	{
		p_vars->hash_table = ft_bins_table_create("PATH=/usr/local/bin:/usr/bin:/bin");
	}

    return (copy);
}


