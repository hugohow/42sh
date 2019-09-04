/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:12:43 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 14:49:03 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H

typedef struct			s_token
{
	char				*type;
	char				*value;
}						t_token;

typedef struct			s_node
{
	long				type;
	char				*cmd;
	char				*cmd_exec;
	char				**args;
	int					nb_child;
	struct s_node		**child;
}						t_node;

typedef struct			s_env
{
	char				*line;
}						t_env;


typedef struct			s_quote
{
	char	*prompt;
	int		cursor;
	int		row;
	int		col;
}						t_quote;

typedef struct			s_context
{
	char	*prompt;
	int		cursor;
}						t_context;

typedef struct			s_cmd
{
	t_list				*head;
	int					last_key;
	long long			size;
	int					len;
	t_context			*context;
}						t_cmd;

typedef struct termios	t_config;

typedef struct			s_vars
{
	t_env				**copy_env;
	t_config			old_config;
	t_config			new_config;
	int					must_exit;
	int					success_exit;
	int					pid;
	char				**argv_list;
	int					argc;
	char				*cwd;
	t_ht				**p_hash_table;
	int					last_key;
	t_cmd				*cmd;
	char				*path_default;
}						t_vars;

typedef int		(t_ft_apply)(t_cmd *);

typedef struct			s_fts_apply
{
	int					key;
	t_ft_apply			*fct;
}						t_fts_apply;
#endif
