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

char	*find_path(char **env)
{
	int		i;
	char	*path_env;

	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	path_env = ft_strnstr(env[i], "PATH=", 5);
	return (path_env + 5);
}

char	*paths_arg(char **paths_sep, char **arg)
{
	char	*temp;
	char	*cmd;
	int		i;

	i = 0;
	while (paths_sep[i])
	{
		temp = ft_strjoin(paths_sep[i], "/");
		cmd = ft_strjoin(temp, arg[0]);
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

void	c_proccess(int status, char *str, char **str_sep, t_t *p)
{
	char    *path_env;
    char    **paths_sep;
    char    *cmd;
	char	**arg;

	(void)status;
	path_env = find_path(var_env);
	paths_sep = ft_split(path_env, ':');
	arg = ft_split(str, ' ');
	cmd = paths_arg(paths_sep, arg);
	if (!cmd)
	{
		p->e_status = 127;
		free_matrix(paths_sep);
		free(cmd);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd, arg, var_env);
	free(str_sep);
}

void	find_cmd(char *str, t_t *p)
{
	pid_t	pid;
	int		status;
	char	**str_sep;

	str_sep = ft_split(str, ' ');
	pid = fork();
	status = 0;
	if (pid == 0)
		c_proccess(status, str, str_sep, p);
	waitpid(pid, &status, 0);
}
