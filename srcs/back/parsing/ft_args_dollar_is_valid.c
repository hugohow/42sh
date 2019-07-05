/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_dollar_is_valid.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:07:26 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/05 17:36:34 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_is_special_param(char c)
{
	if (c == '*' || c == '@' || c == '#' || c == '?'|| c == '-' || c == '$' || c == '!')
		return (1);
	return (0);
}

static int ft_args_dollar_is_valid_whitout_braces(char *str)
{
	int ret;

	ret = 1;
	if (ft_isdigit(str[ret]))
		return (ret + 1);
	if (ft_is_special_param(str[ret]))
		return (ret + 1);
	while (str[ret] && str[ret] != '/')
	{
		if (ft_isalnum(str[ret]) == 0 && str[ret] != '_')
			break ;
		ret++;
	}
	return (ret);
}

/*
** echo ${*1} -> return (-1);
** echo ${1D} -> return (-1);
** echo ${12} -> ok;
** echo ${ABS} -> ok;
** echo ${1*} -> return (-1);
*/


static int ft_args_dollar_is_valid_braces(char *str)
{
	int ret;

	ret = 2;
	if (ft_isdigit(str[ret]))
	{
		ret++;
		while (str[ret] && str[ret] != '}' && ft_isdigit(str[ret]))
			ret++;
		if (str[ret] == 0 || str[ret] != '}')
			return (-1);
		return (ret + 1);
	}
	if (ft_is_special_param(str[ret]))
	{
		ret++;
		if (str[ret] != '}')
			return (-1);
		return (ret + 1);
	}
	while (str[ret] && str[ret] != '}')
	{
		if (ft_is_special_param(str[ret]))
			return (-1);
		if (ft_isalnum(str[ret]) == 0 && str[ret] != '_')
			return (-1);
		ret++;
	}
	if (str[ret] == 0)
		return (-1);
	return (ret + 1);
}

/*
** lenght of {PATH} or $@
*/

int ft_args_dollar_is_valid(char *str)
{
	int ret;

	ret = 1;
	if (str[ret] == 0)
		return (0);
	if (str[ret] == '{')
		return (ft_args_dollar_is_valid_braces(str));
	else
		return (ft_args_dollar_is_valid_whitout_braces(str));
	return (ret);
}