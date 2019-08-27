#include "closures.h"

static void		read_input(t_cmd *cmd)
{
	int		ret;
	t_quote	a;

	memset(&a, '\0', sizeof(t_quote));
	a.prompt = "dquote> ";
	cmd->arg = &a;
	ret = 0;
	ft_quote_apply_enter(cmd);
	while (1)
	{
		ret = ft_interactive_read_key();
		if (ret == KEY_TERM_ENTER
			&& cmd->last_key == '"') {
			if (!check_closures(cmd->head, "\""))
				return ;
		}
		cmd->last_key = ret;
		ft_quote_apply_key(cmd);
	}
}

char		*parse_dquote(void)
{
	t_vars	*p_vars;
	p_vars = ft_vars_get();

	if (check_closures((p_vars->cmd)->head, "\""))
		read_input(p_vars->cmd);
	fflush(stdout);
	return (NULL);
}