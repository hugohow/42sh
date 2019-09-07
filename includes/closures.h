#ifndef CLOSURES_H
# define CLOSURES_H
// File to delete later
# include "shell.h"


void		ft_complete_add_printable(t_cmd *cmd, int c);
int	        ft_get_current_column(t_context *context);
int			check_closures(t_list *list, char *closures);
void		right_call(t_cmd *cmd);

#endif