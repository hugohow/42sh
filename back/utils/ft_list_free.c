/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 21:21:11 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/25 10:27:40 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_list_free(char **list)
{
	size_t i;

	i = 0;
	while (list && list[i])
	{
		ft_memdel((void **)(&(list[i])));
		i++;
	}
	ft_memdel((void **)(list));
}