/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 22:25:42 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 22:35:31 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_cmd *ft_cmd_init(t_env **copy_env)
{
	t_cmd *cmd;

	cmd = (t_cmd *)ft_memalloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->head = ft_lstnew(0, 0);
	cmd->size = 0;
	cmd->len = 0;
	cmd->last_key = 0;
	cmd->copy_env = copy_env;
	return (cmd);
}

static int ft_stdin_get_cmd(int fd, char **command, t_env **copy_env)
{	
    char ret;
	t_list *head;
	char *join;
	t_cmd *cmd;
	int end;

	cmd = ft_cmd_init(copy_env);
	head = cmd->head;
	end = 0;
	while (42)
	{
		if ((read(fd, &ret, sizeof(char)) == 0))
		{
			end = 1;
			break ;
		}		
		cmd->last_key = (int)ret;
		if (ret == '\n' || ret == '\0')
			break ;
		ret = ft_apply_key(cmd, 0);
		if (ret == 0)
			break ;
	}
	join = ft_node_join(cmd->head, cmd->size);
	*command = ft_strrchr(join, '\n');
	if (*command == NULL)
		*command = ft_strdup(join);
	else
		*command = ft_strdup(ft_strrchr(join, '\n'));
	ft_memdel((void **)&join);
	ft_lstfree(cmd->head);
	ft_memdel((void **)&cmd);
    return (end);
}

int ft_stdin_exec(t_env ***p_copy_env, char **argv)
{
	char *command;
	t_node *root;
	int success;
	int fds[3];
	int fd;
	int end;

	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;
	success = 0;
	fd = ft_isatty(0) == 0 ? 0 : open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_env_free(p_copy_env);
		ft_dprintf(fds[2], "shell: %s: No such file or directory\n", argv[1]);
		exit(EXIT_UTILITY_NOT_FOUND);
	}
	end = 0;
	while (42)
	{


		end = ft_stdin_get_cmd(fd, &command, *p_copy_env);



		root = ft_syntax_tree_create(command, *p_copy_env);
		ft_execute_tree(root, p_copy_env, fds, &success);
		ft_syntax_tree_free(&root);
		ft_memdel((void **)&command);
		if (ft_env_get_value(*p_copy_env, "EXIT") && ft_strchr(ft_env_get_value(*p_copy_env, "EXIT"), '1'))
			break ;
		if (end == 1)
			break;
	}
	if (fd != 0)
		close(fd);
	return (success);
}
