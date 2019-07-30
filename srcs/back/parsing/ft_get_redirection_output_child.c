/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirection_output_child.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 11:39:35 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/30 18:43:25 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


int			ft_get_redirection_input(t_node *node, char *cpy_cmd)
{
	int i;
	int j;
	int k;

	i = 0;
	while ((cpy_cmd)[i])
	{
		if ((cpy_cmd)[i] == '<' && (cpy_cmd)[i + 1] != '<')
		{
			t_node *node_redirection;

			if (!(node_redirection = (t_node *)ft_memalloc(sizeof(t_node))))
				return (-1);
			(node_redirection)->type = TYPE_REDIRECTION_INPUT;
			(node_redirection)->cmd = ft_strdup(cpy_cmd + i);
			(node_redirection)->cmd_exec = NULL;
			(node_redirection)->args = NULL;
			(node_redirection)->nb_child = -1;

			(node_redirection)->n = 0;
			(node_redirection)->digit = -1;
			(node_redirection)->word = NULL;
			
			k = 0;
			while (i - k > 0 && ft_isdigit((cpy_cmd)[i - k]))
				k++;
			(node_redirection)->n = ft_atoi(cpy_cmd + i - k);
			(node_redirection)->word = ft_strdup(cpy_cmd + i + 1);
			j = 0;
			while ((node_redirection)->word[j] == ' ')
				j++;
			while (ft_isalnum((node_redirection)->word[j]))
			{
				cpy_cmd[i + 1 + j] = ' ';
				j++;
			}
			(node_redirection)->word[j] = 0;
			while (k != 0)
			{
				cpy_cmd[i - k] = ' ';
				k--;
			}
			cpy_cmd[i] = ' ';
			k = 0;
			
			while (node->child[k])
				k++;
			printf("node_redirection %d, n : %d, digit : %d, word: %s\n", k, (node_redirection)->n, (node_redirection)->digit, (node_redirection)->word);
			node->child[k] = node_redirection;
			node->child[k + 1] = 0;
			
		}
		i++;
	}
	return (0);
}

// define TYPE_REDIRECTION_INPUT  [n]<word
// # define TYPE_REDIRECTION_OUTPUT [n]>[|]word
// # define TYPE_REDIRECTION_APPENDING_OUTPUT [n]>>word
// # define TYPE_REDIRECTION_STDOUT_STDERR &>word   >&word   >word 2>&1
// # define TYPE_REDIRECTION_APPENDING_STDOUT_STDERR   &>>word   >>word 2>&1
// # define TYPE_REDIRECTION_HERE_DOCUMENT    
// [n]<<[−]word
// 		here-document
// delimiter
// # define TYPE_REDIRECTION_HERE_STRING [n]<<< word
// # define TYPE_REDIRECTION_DUPLICATING_FD   [n]<&word     [n]>&word
// # define TYPE_REDIRECTION_MOVING_FD           [n]<&digit        [n]>&digit
// # define TYPE_REDIRECTION_OPEN_FD         [n]<>word


int			ft_get_redirection_output_child(t_node *node, t_env **copy_env)
{
	char *cpy_cmd;

	(void)copy_env;

	if (ft_strchr(node->cmd, '>') == NULL && ft_strchr(node->cmd, '<') == NULL)
		return (0);
	printf("parsing of : %s\n", node->cmd);
	node->child = ft_memalloc(999*sizeof(t_node *));
	cpy_cmd = ft_strdup(node->cmd);
	printf("cpy_cmd : %s\n", cpy_cmd);
	ft_get_redirection_input(node, cpy_cmd);
	printf("cpy_cmd : %s\n", cpy_cmd);
	node->type = TYPE_REDIRECTED;
	return (0);
	// k = 0;
	// child[0] = create_node(TYPE_BASE, list[0], copy_env);
	// k++;
	// while (list[k])
	// {
	// 	if (!(child[k] = (t_node *)ft_memalloc(sizeof(t_node))))
	// 		return (-1);
	// 	(child[k])->type = TYPE_REDIRECTION_OUTPUT;
	// 	(child[k])->cmd = ft_strdup(list[k]);
	// 	(child[k])->cmd_exec = NULL;
	// 	(child[k])->args = NULL;
	// 	(child[k])->nb_child = -1;
	// 	k++;
	// }
	// node->nb_child = k;
	// node->type = TYPE_REDIRECTED;
	// ft_list_free(&list);
	// node->child = child;
	// return (0);
}
