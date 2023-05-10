/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:02:15 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/09 13:02:17 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	exec_cmd(char **str_sep, t_shell *p)
{
	char	*path_env;
	char	**paths_sep;
	char	*cmd;

	path_env = find_path(p);
	if (!path_env)
	{
		error_nofile(str_sep[0]);
		free_matrix(str_sep);
		exit(127);
	}
	paths_sep = ft_split(path_env, ':');
	cmd = paths_arg(paths_sep, str_sep);
	if (!cmd)
	{
		free_matrix(paths_sep);
		error_cmd(str_sep[0]);
		free_matrix(str_sep);
		exit(127);
	}
	free_matrix(paths_sep);
	execve(cmd, str_sep, p->var_env);
}

void	exec(char *str, t_shell *p)
{
	char	**str_sep;

	str_sep = ft_split(str, ' ');
	if (p->interp == 0)
		str_sep[1] = NULL;
	str_sep[0] = ft_strtrim(str_sep[0], " ");
	if (check_builtin(str_sep[0]))
		do_builtin(str, p);
	else
		exec_cmd(str_sep, p);
	exit(0);
}

void	child_pipe(t_shell *p, int *prevpipe, char *str, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	p->fd_out = fd[1];
	close(fd[1]);
	dup2(*prevpipe, STDIN_FILENO);
	close(*prevpipe);
	if (check_redir(str))
		do_redir_pipe(str, p);
	else
		exec(str, p);
}

void	last_child(int *prevpipe, char *str, t_shell *p)
{
	dup2(*prevpipe, STDIN_FILENO);
	close(*prevpipe);
	if (check_redir(str))
		do_redir_pipe(str, p);
	else
		exec(str, p);
}
