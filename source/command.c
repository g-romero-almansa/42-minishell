/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:41:26 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/03 13:06:55 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*find_path(t_shell *p)
{
	int		i;
	char	*path_env;

	i = 0;
	while (i < p->env_n && (!ft_strnstr(p->var_env[i], "PATH=", 5)))
		i++;
	if (i == p->env_n && (!ft_strnstr(p->var_env[i], "PATH=", 5)))
		return (NULL);
	path_env = ft_strnstr(p->var_env[i], "PATH=", 5);
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

void	c_proccess(t_shell *p)
{
	char	*path_env;
	char	**paths_sep;
	char	*cmd;
	char	**arg;

	arg = ft_split(p->pipes[0]->str, ' ');
	if (p->interp == 0)
		arg[1] = NULL;
	execve(arg[0], arg, p->var_env);
	path_env = find_path(p);
	if (!path_env)
	{
		error_nofile(p->pipes[0]->str);
		exit(127);
	}
	paths_sep = ft_split(path_env, ':');
	cmd = paths_arg(paths_sep, arg);
	if (!cmd)
	{
		free_matrix(paths_sep);
		error_cmd(p->pipes[0]->str);
		exit(127);
	}
	free_matrix(paths_sep);
	execve(cmd, arg, p->var_env);
}

void	find_cmd(t_shell *p)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		g_error = errno;
		perror("Error: ");
	}
	else if (pid == 0)
		c_proccess(p);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_error = WEXITSTATUS(status);
}
