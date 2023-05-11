/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:24:07 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/09 12:24:09 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	out_child(char *file, char *str, t_shell *p)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		g_error = errno;
		perror("Error en open");
		exit(errno);
	}
	p->fd_out = fd;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec(str, p);
}

void	double_out_child(char *file, char *str, t_shell *p)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		g_error = errno;
		perror("Error: ");
		exit(errno);
	}
	p->fd_out = fd;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec(str, p);
}

void	output_redir(char *str, t_shell *p)
{
	char	**redir_sep;
	char	*temp1;
	char	*temp2;
	pid_t	child_pid;
	int		status;

	redir_sep = ft_split(str, '>');
	temp1 = ft_strtrim(redir_sep[0], " ");
	free(redir_sep[0]);
	redir_sep[0] = temp1;
	temp2 = ft_strtrim(redir_sep[1], " ");
	free(redir_sep[1]);
	redir_sep[1] = temp2;
	child_pid = fork();
	if (child_pid == -1)
		std_error();
	else if (child_pid == 0)
		out_child(redir_sep[1], redir_sep[0], p);
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
	}
	free_matrix(redir_sep);
}

char	**sep_redir(char *str)
{
	char	**redir_sep;
	char	*temp1;
	char	*temp2;

	redir_sep = ft_split(str, '>');
	temp1 = ft_strtrim(redir_sep[0], " ");
	free(redir_sep[0]);
	redir_sep[0] = temp1;
	temp2 = ft_strtrim(redir_sep[1], "> ");
	free(redir_sep[1]);
	redir_sep[1] = temp2;
	return (redir_sep);
}

void	double_output(char *str, t_shell *p)
{
	char	**redir_sep;
	int		fd;
	pid_t	child_pid;
	int		status;

	redir_sep = sep_redir(str);
	child_pid = fork();
	fd = 0;
	if (child_pid == -1)
		std_error();
	else if (child_pid == 0)
		double_out_child(redir_sep[1], redir_sep[0], p);
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
	}
	free_matrix(redir_sep);
}
