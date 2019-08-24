#ifndef CLOSURES_H
# define CLOSURES_H

# include "shell.h"

int			check_closures(t_list *list, char *closures);
void		on_enter_key(t_cmd *cmd);
void		on_key_press(t_cmd *cmd);

#endif