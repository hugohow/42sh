/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:43:49 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 17:44:17 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	ft_list_size(char **list)
{
	size_t size;

	if (list == NULL)
		return (-1);
	size = 0;
	while (list[size])
		size++;
	return (size);
}
