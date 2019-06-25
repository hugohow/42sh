/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:41:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/25 10:23:11 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	set_result(int success, t_env ***p_environ)
{
	char *success_str;

	success_str = ft_itoa(success);
	if (success_str == NULL)
		return ;
	ft_env_change_line("?", ft_strjoin("?=", success_str), *p_environ);
	ft_memdel((void **)&success_str);
}

void    execute_tree(t_node *node, t_env ***p_environ, int fds[], int *p_success)
{
	if (node == NULL)
		return ;
    if (node && node->type & TYPE_CMD)
    {
		*p_success = ft_exe_bin(node, p_environ, fds);
		set_result(*p_success, p_environ);
    }
    if (node && node->child && *(node->child))
    {
        while (*(node->child))
        {
            execute_tree(*(node->child), p_environ, fds, p_success);
            node->child++;
        }
    }
}