/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:45:49 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/03 13:11:49 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_pipe(char *str, int *prevpipe, int i, t_shell *p)
{
	int	fd[2];

	if (pipe(fd) < 0)
	{
		std_error();
		exit(errno);
	}
	p->child_pid[i] = fork();
	if (p->child_pid[i] == -1)
		std_error();
	else if (p->child_pid[i] == 0)
		child_pipe(p, prevpipe, str, fd);
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
		std_error();
	else if (p->child_pid[i] == 0)
		last_child(prevpipe, str, p);
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

void	do_pipes(t_shell *p)
{
	int	prevpipe;
	int	i;

	prevpipe = dup(0);
	if (prevpipe == -1)
		std_error();
	p->child_pid = (pid_t *)malloc(sizeof(pid_t) * (p->n_pipes + 1));
	if (!p->child_pid)
		std_error();
	i = 0;
	while (i <= p->n_pipes)
	{
		if (p->pipes[i] && p->pipes[i + 1])
			ft_pipe(p->pipes[i]->str, &prevpipe, i, p);
		if (i == p->n_pipes)
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
