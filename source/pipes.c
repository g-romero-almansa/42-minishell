/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:45:49 by barbizu-          #+#    #+#             */
/*   Updated: 2023/04/27 10:22:23 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	exec(char *str, t_shell *p)
{
	char	*path_env;
	char	**paths_sep;
	char	**str_sep;
	char	*cmd;

	str_sep = ft_split(str, ' ');
	if (p->interp == 0)
		str_sep[1] = NULL;
	str_sep[0] = ft_strtrim(str_sep[0], " ");
	if (check_builtin(str_sep[0]))
	{
		do_builtin(str, p);
		exit(0);
	}
	else
	{
		path_env = find_path(p);
		if (!path_env)
		{
			ft_putstr_fd(str_sep[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
			free_matrix(str_sep);
			g_error = 127;
			exit(127);
		}
		paths_sep = ft_split(path_env, ':');
		cmd = paths_arg(paths_sep, str_sep);
		if (!cmd)
		{
			free_matrix(paths_sep);
			ft_putstr_fd(str_sep[0], 2);
			ft_putendl_fd(": command not found", 2);
			free_matrix(str_sep);
			g_error = 127;
			exit(127);
		}
		free_matrix(paths_sep);
		execve(cmd, str_sep, p->var_env);
	}
}

void	ft_pipe(char *str, int *prevpipe, int i, t_shell *p)
{
	int	fd[2];

	if (pipe(fd) < 0)
	{
		g_error = errno;
		perror("Error: ");
		exit(errno);
	}
	p->child_pid[i] = fork();
	if (p->child_pid[i] == -1)
	{
		g_error = errno;
		perror("Error: ");
	}
	else if (p->child_pid[i] == 0)
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
	else
	{
		close(fd[1]);
		close(*prevpipe);
		*prevpipe = fd[0];
	}
}

void	ft_last(char *str, int *prevpipe, int i, t_shell *p)
{
	int	j;
	int	status;

	p->child_pid[i] = fork();
	if (p->child_pid[i] == -1)
	{
		g_error = errno;
		perror("Error: ");
	}
	else if (p->child_pid[i] == 0)
	{
		dup2(*prevpipe, STDIN_FILENO);
		close(*prevpipe);
		if (check_redir(str))
			do_redir_pipe(str, p);
		else
			exec(str, p);
	}
	else
	{
		close(*prevpipe);
		j = 0;
		while (j <= p->n_pipes)
		{
			waitpid(p->child_pid[j], &status, 0);
			if (WIFEXITED(status))
				g_error = WEXITSTATUS(status);
			j++;
		}
	}
}

void	do_pipes(char *str, t_shell *p)
{
	int	prevpipe;
	int	i;

	(void)str;
	prevpipe = dup(0);
	if (prevpipe == -1)
	{
		g_error = errno;
		perror("Error: ");
	}
	p->child_pid = (pid_t *)malloc(sizeof(pid_t) * (p->n_pipes + 1));
	if (!p->child_pid)
	{
		g_error = errno;
		perror("Error: ");
	}
	i = 0;
	while (i <= p->n_pipes)
	{
		if (p->pipes[i] && p->pipes[i + 1])
			ft_pipe(p->pipes[i]->str, &prevpipe, i, p);
		else if (p->pipes[i + 1] == NULL)
			ft_last(p->pipes[i]->str, &prevpipe, i, p);
		i++;
	}
	free(p->child_pid);
}

int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}
