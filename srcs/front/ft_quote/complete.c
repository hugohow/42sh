#include "closures.h"

static void		read_input(void)
{
	int		ret;
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	ret = 0;
	ft_quote_apply_enter(p_vars->cmd);
	while (1)
	{
		ret = ft_interactive_read_key();
		if (ret == KEY_TERM_ENTER
			&& p_vars->cmd->last_key == '"') {
			if (!check_closures(p_vars->cmd->head, "\""))
				return ;
		}
		(p_vars->cmd)->last_key = ret;
		ft_quote_apply_key(p_vars->cmd);
	}
}

char		*parse_dquote(void)
{
	t_vars	*p_vars;
	p_vars = ft_vars_get();

	if (check_closures((p_vars->cmd)->head, "\""))
		read_input();
	fflush(stdout);
	return (NULL);
}