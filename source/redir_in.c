/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:35:08 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/11 12:13:07 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	child_input(char *file, char *str, t_shell *p)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
	{
		g_error = errno;
		perror("Error: ");
		exit(errno);
	}
	p->fd_out = fd;
	dup2(fd, STDIN_FILENO);
	close(fd);
	exec(str, p);
}

void	input_redir(char *str, t_shell *p)
{
	char	**redir_sep;
	pid_t	child_pid;
	int		status;
	char	*temp1;

	redir_sep = ft_split(str, '<');
	temp1 = ft_strtrim(redir_sep[0], " ");
	free(redir_sep[0]);
	redir_sep[0] = temp1;
	temp1 = ft_strtrim(redir_sep[1], " ");
	free(redir_sep[1]);
	redir_sep[1] = temp1;
	child_pid = fork();
	if (child_pid == -1)
		std_error();
	else if (child_pid == 0)
		child_input(redir_sep[1], redir_sep[0], p);
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
	}
	free_matrix(redir_sep);
}

void	double_child_input(t_shell *p, char *delim)
{
	char	*buffer;
	char	*gnl;

	buffer = ft_strdup("");
	p->fd_out = STDOUT_FILENO;
	gnl = readline("> ");
	while (gnl)
	{
		if ((ft_strlen(gnl) == ft_strlen(delim)) && !ft_strncmp(gnl,
				delim, ft_strlen(delim)))
		{
			ft_putstr_fd(buffer, p->fd_out);
			free(gnl);
			free(buffer);
			exit(0);
		}
		buffer = ft_strjoin(buffer, gnl);
		buffer = ft_strjoin(buffer, "\n");
		free(gnl);
		gnl = readline("> ");
	}
}

void	double_input(char *str, t_shell *p)
{
	char	**redir_sep;
	pid_t	child_pid;
	int		status;
	char	*temp1;

	redir_sep = ft_split(str, '<');
	temp1 = ft_strtrim(redir_sep[0], " ");
	free(redir_sep[0]);
	redir_sep[0] = temp1;
	temp1 = ft_strtrim(redir_sep[1], " ");
	free(redir_sep[1]);
	redir_sep[1] = temp1;
	child_pid = fork();
	if (child_pid == -1)
		std_error();
	else if (child_pid == 0)
		double_child_input(p, redir_sep[1]);
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
	}
	free_matrix(redir_sep);
}
