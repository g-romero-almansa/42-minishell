/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:33:32 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/03 13:12:11 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	input_redir_pipe(char *str, t_shell *p)
{
	char	**redir_sep;
	int		fd;

	redir_sep = ft_split(str, '<');
	redir_sep[0] = ft_strtrim(redir_sep[0], " ");
	redir_sep[1] = ft_strtrim(redir_sep[1], " ");
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
	exec(redir_sep[0], p);
	free_matrix(redir_sep);
}

void	output_redir_pipe(char *str, t_shell *p)
{
	char	**redir_sep;
	int		fd;

	redir_sep = ft_split(str, '>');
	redir_sep[0] = ft_strtrim(redir_sep[0], " ");
	redir_sep[1] = ft_strtrim(redir_sep[1], " ");
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
	exec(redir_sep[0], p);
	free_matrix(redir_sep);
}

void	double_output_pipe(char *str, t_shell *p)
{
	char	**redir_sep;
	int		fd;

	redir_sep = ft_split(str, '>');
	redir_sep[0] = ft_strtrim(redir_sep[0], " ");
	redir_sep[1] = ft_strtrim(redir_sep[1], "> ");
	fd = open(redir_sep[1], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		g_error = errno;
		perror("Error: ");
		exit(errno);
	}
	p->fd_out = fd;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec(redir_sep[0], p);
	free_matrix(redir_sep);
}

void	do_redir_pipe(char *str, t_shell *p)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
			double_output_pipe(str, p);
		else if (str[i] == '<' && str[i - 1] != '<')
			input_redir_pipe(str, p);
		else if (str[i] == '>' && str[i - 1] != '>')
			output_redir_pipe(str, p);
		i++;
	}
}
