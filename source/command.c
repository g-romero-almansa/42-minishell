/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:41:26 by barbizu-          #+#    #+#             */
/*   Updated: 2023/02/01 10:41:30 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*find_path(char **var_env)
{
	int		i;
	char	*path_env;

	i = 0;
	while (!ft_strnstr(var_env[i], "PATH=", 5))
		i++;
	path_env = ft_strnstr(var_env[i], "PATH=", 5);
	return (path_env + 5);
}

char	*ft_paths_arg(char **paths_sep, char *str)
{
	char	*temp;
	char	*cmd;
	int		i;

	i = 0;
	while (paths_sep[i])
	{
		temp = ft_strjoin(paths_sep[i], "/");
		cmd = ft_strjoin(temp, str);
		free(temp);
		if (!access(cmd, F_OK))
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void    find_cmd(char *str, char **var_env, char **argv)
{
    char    *path_env;
    char    **paths_sep;
    char    *cmd;
	pid_t	pid;
	int		status;

    pid = fork();
	status = 0;
	if (pid == 0)
	{
		path_env = find_path(var_env);
		paths_sep = ft_split(path_env, ':');
		cmd = ft_paths_arg(paths_sep, str);
		if (!cmd)
		{
			free_matrix(paths_sep);
			free(cmd);
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": command not found", 2);
			exit(status);
		}
		execve(cmd, argv, var_env);
	}
	else
		waitpid(pid, &status, 0);
}