/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:59:58 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/14 00:14:48 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_apply_tab(t_cmd *cmd)
{
	char	*complete;
	char	*str;
	t_list	*node;
	t_list	*head;
	char	*join;

	head = cmd->head;
	join = ft_node_join(head, cmd->size + 2);
	str = ft_strrchr(join, ';');
	if (str == NULL)
		str = join;
	else
		str++;
	complete = ft_env_autocomplete_cmd(str);
	if (complete)
	{
		ft_putstr_fd(complete, 0);
		node = ft_lstnew((void *)complete,\
			((ft_strlen(complete) + 1) * sizeof(char)));
		ft_lstinsert(&head, node);
		cmd->size = cmd->size + ((ft_strlen(complete) + 1) * sizeof(char));
		ft_memdel((void **)&complete);
	}
	ft_memdel((void **)&join);
	return (1);
}
