#include "shell.h"

int		ft_complete_check(t_list *list, char *closures)
{
	char	c;
	int		escape;
	int		open;

	open = 0;
	escape = 0;
	while (list)
	{
		if (list->content)
		{
			c = *(char*)list->content;
			if (closures[1] && c == closures[0] && !escape && open)
				return (1);
			if (!escape && (c == closures[0] || (closures[1] && c == closures[1])))
				open = !open;
			escape = (c == '\\') ? !escape : 0;
		}
		list = list->next;
	}
	return (open);
}