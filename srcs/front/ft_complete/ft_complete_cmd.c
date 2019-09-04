/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:07:32 by kesaint-          #+#    #+#             */
/*   Updated: 2019/09/04 16:07:42 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_complete(const char *prompt)
{
	int		ret;

	while (42)
	{
		ret = ft_interactive_read_key();
		if (ret == KEY_TERM_ENTER && cmd->last_key == '"')
		{

		}
		cmd->last_key = ret;
		ft_complete_apply_key(cmd);
	}
}

char		*ft_complete_cmd(void)
{
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	if (check_closures(p_vars->cmd->head, "\""))
		ft_complete("dquote> ");
	return (NULL);
}
