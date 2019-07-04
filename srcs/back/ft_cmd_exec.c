/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 02:17:21 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 03:30:19 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_cmd_exec(char *command, t_env ***p_copy_env, int fds[], int *p_success)
{
	t_node *root;
	
	if (command == NULL)
		return ;
	root = ft_syntax_tree_create(command, *p_copy_env);
	ft_syntax_tree_execute(root, p_copy_env, fds, p_success);
	ft_syntax_tree_free(&root);
	ft_memdel((void **)&command);
}