/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:20 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 14:56:36 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to get the environnement of the process
*/

void		ft_print_env(t_env **cpy_env, int fds[])
{
	int i;

	i = 0;
	while (cpy_env[i])
	{
		ft_putstr_fd(cpy_env[i]->line, fds[1]);
		ft_putstr_fd("\n", fds[1]);
		i++;
	}
}

t_env		**clear_environ(void)
{
	t_env **output;

	if (!(output = (t_env **)ft_memalloc((sizeof(t_env *) + 1))))
		return (NULL);
	return (output);
}

static char	*ft_env_get_cmd(char **argv)
{
	int		i;
	int		len;
	char	*cmd;

	i = 0;
	len = 0;
	while (argv[i])
	{
		len += ft_strlen(argv[i]) + 2;
		i++;
	}
	if (!(cmd = (char *)ft_memalloc(len * sizeof(char))))
		return (NULL);
	i = 0;
	while (argv[i])
	{
		cmd = ft_strcat(cmd, argv[i]);
		cmd = ft_strcat(cmd, " ");
		i++;
	}
	return (cmd);
}

static int	ft_execute_env(char **argv, t_env ***p_copy_env, int fds[])
{
	int		success;
	char	*cmd;
	t_ht	**p_table_bins;

	if (!(p_table_bins = (t_ht **)ft_memalloc(sizeof(t_ht *))))
		return (1);
	argv = ft_env_complete_env(argv, p_copy_env, p_table_bins);
	if (*argv)
	{
		cmd = ft_env_get_cmd(argv);
		if (*p_table_bins == NULL)
			ft_cmd_exec(cmd, p_copy_env, NULL, fds);
		else
			ft_cmd_exec(cmd, p_copy_env, p_table_bins, fds);
	}
	else
		ft_print_env(*p_copy_env, fds);
	ft_ht_free(p_table_bins);
	ft_memdel((void **)&(p_table_bins));
	success = *((int *)ft_vars_get_value(KEY_SUCCESS_EXIT));
	return (success);
}

int			ft_env(char **argv, t_env **cpy_environ, int fds[])
{
	int		status;
	int		flag;
	t_env	**copy_env;

	argv++;
	if (ft_list_size(argv) == 0)
	{
		ft_print_env(cpy_environ, fds);
		return (0);
	}
	flag = ft_env_parse(&argv, fds);
	if (flag < 0)
		return (1);
	if (flag == FLAG_ENV_I)
		copy_env = clear_environ();
	else
		copy_env = ft_env_deep_copy(cpy_environ);
	if (copy_env == NULL)
	{
		ft_putstr_fd("Error copy env\n", 2);
		return (1);
	}
	status = ft_execute_env(argv, &copy_env, fds);
	ft_env_free(&copy_env);
	return (status);
}
