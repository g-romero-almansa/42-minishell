/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:19:50 by gromero-          #+#    #+#             */
/*   Updated: 2023/04/27 10:19:28 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	input_redir(char *str, t_shell *p)
{
	char	**redir_sep;
	int		fd;
	pid_t	child_pid;
	int		status;

	redir_sep = ft_split(str, '<');
	redir_sep[0] = ft_strtrim(redir_sep[0], " ");
	redir_sep[1] = ft_strtrim(redir_sep[1], " ");
	child_pid = fork();
	if (child_pid == -1)
	{	
		g_error = errno;
		perror("Error: ");
	}
	else if (child_pid == 0)
	{
		fd = open(redir_sep[1], O_RDONLY, 0644);
		if (fd == -1)
		{
			g_error = errno;
			perror("Error: ");
			exit(errno);
		}
		p->fd_out = fd;
		dup2(fd, STDIN_FILENO);
		close(fd);
		exec(redir_sep, 0, p);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
	}
}

void	output_redir(char *str, t_shell *p)
{
	char	**redir_sep;
	int		fd;
	pid_t	child_pid;
	int		status;

	redir_sep = ft_split(str, '>');
	redir_sep[0] = ft_strtrim(redir_sep[0], " ");
	redir_sep[1] = ft_strtrim(redir_sep[1], " ");
	child_pid = fork();
	if (child_pid == -1)
	{	
		g_error = errno;
		perror("Error: ");
	}
	else if (child_pid == 0)
	{
		fd = open(redir_sep[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			g_error = errno;
			perror("Error en open");
			exit(errno);
		}
		p->fd_out = fd;
		dup2(fd, STDOUT_FILENO);
		close(fd);
		exec(redir_sep, 0, p);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
	}
}

void	double_input(char *str, t_shell *p)
{
	char	**redir_sep;
	char	*gnl;
	pid_t	child_pid;
	int		status;
	char	*buffer;

	redir_sep = ft_split(str, '<');
	redir_sep[0] = ft_strtrim(redir_sep[0], " ");
	redir_sep[1] = ft_strtrim(redir_sep[1], "< ");
	child_pid = fork();
	if (child_pid == -1)
	{
		g_error = errno;
		perror("Error: ");
	}
	else if (child_pid == 0)
	{
		buffer = ft_strdup("");
		p->fd_out = STDOUT_FILENO;
		gnl = readline("> ");
		while (gnl)
		{
			if ((ft_strlen(gnl) == ft_strlen(redir_sep[1])) && !ft_strncmp(gnl, redir_sep[1], ft_strlen(redir_sep[1])))
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
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
	}
}

void	double_output(char *str, t_shell *p)
{
	char	**redir_sep;
	int		fd;
	pid_t	child_pid;
	int		status;

	redir_sep = ft_split(str, '>');
	redir_sep[0] = ft_strtrim(redir_sep[0], " ");
	redir_sep[1] = ft_strtrim(redir_sep[1], "> ");
	child_pid = fork();
	if (child_pid == -1)
	{
		g_error = errno;
		perror("Error: ");
	}
	else if (child_pid == 0)
	{
		fd = open(redir_sep[1], O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
		{
			g_error = errno;
			perror("Error: ");
			exit(errno);
		}
		p->fd_out = fd;
		dup2(fd, STDOUT_FILENO);
		exec(redir_sep, 0, p);
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
	}
}

void	do_redir(char *str, t_shell *p)
{
	int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '<' && str[i + 1] == '<')
			double_input(str, p);
		else if (str[i] == '>' && str[i + 1] == '>')
			double_output(str, p);
		else if (str[i] == '<' && str[i - 1] != '<')
            input_redir(str, p);
		else if (str[i] == '>' && str[i - 1] != '>')
			output_redir(str, p);
        i++;
    }
}

int	check_redir(char *str)
{
	int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '<' || str[i] == '>')
            return (1);
        i++;
    }
    return (0);
}
