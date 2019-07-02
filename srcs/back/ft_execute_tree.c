/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:24:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/02 03:54:36 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	set_result(int success, t_env ***p_environ)
{
	char *success_str;
	char *line;
	char *prefix;

	success_str = ft_itoa(success);
	if (success_str == NULL)
		return ;
	prefix = ft_strdup("?");
	line = ft_strjoin("?=", success_str);
	ft_env_change_line("?", line, *p_environ);
	ft_memdel((void **)&success_str);
	ft_memdel((void **)&prefix);
}

void    ft_execute_tree(t_node *node, t_env ***p_environ, int fds[], int *p_success)
{
	int k;

	if (node == NULL)
		return ;
    if (node && node->type & TYPE_CMD)
    {
		*p_success = ft_exe_bin(node, p_environ, fds);
		set_result(*p_success, p_environ);
    }
	k = 0;
    if (node && node->child && node->child[k])
    {
        while (node->child[k])
        {
            ft_execute_tree(node->child[k], p_environ, fds, p_success);
			if ((node->child[k])->args == NULL)
				return ;
			if (ft_env_get_value(*p_environ, "EXIT") && ft_strchr(ft_env_get_value(*p_environ, "EXIT"), '1'))
				return ;
            k++;
        }
    }
}