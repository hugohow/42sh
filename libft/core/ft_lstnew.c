/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:13:35 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 14:04:59 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*new_content;

	if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new_content = (void *)ft_memalloc(content_size)))
		{
			ft_memdel((void **)&new);
			return (NULL);
		}
		ft_memcpy(new_content, content, content_size);
		new->content = new_content;
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
