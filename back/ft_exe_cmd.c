/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:41:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/24 16:36:37 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    execute_tree(t_node *node, t_env ***p_environ, int fds[], int *p_success)
{
	if (node == NULL)
		return ;
    if (node && node->type & TYPE_CMD)
    {
		*p_success = ft_exe_bin(node, p_environ, fds);
		ft_env_change_line("?", ft_strjoin("?=", ft_itoa(*p_success)), *p_environ);
    }
    if (node && node->child)
    {
        int k;

        k = 0;
        while (node->child[k])
        {
            t_node *node_child;

            node_child = node->child[k];
            execute_tree(node_child, p_environ, fds, p_success);
            k++;
        }
    }
}