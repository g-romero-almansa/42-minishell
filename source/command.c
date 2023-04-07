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

char	*find_path(t_shell *p)
{
	int		i;
	char	*path_env;

	i = 0;
	while (i < p->env_n && (!ft_strnstr(p->var_env[i], "PATH=", 5)))
		i++;
	if (i == p->env_n)
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

void	c_proccess(char *str, t_shell *p)
{
	char    *path_env;
    char    **paths_sep;
    char    *cmd;
	char	**arg;

	arg = ft_split(str, ' ');
	execve(str, arg, p->var_env);
	path_env = find_path(p);
	if (!path_env)
	{
		free(arg);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_error = 127;
		exit(127);
	}
	paths_sep = ft_split(path_env, ':');
	cmd = paths_arg(paths_sep, arg);
	if (!cmd)
	{
		free_matrix(paths_sep);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
		g_error = 127;
		exit(127);
	}
	execve(cmd, arg, p->var_env);
}

void	find_cmd(char *str, t_shell *p)
{
	pid_t	pid;
	int		status;
	char	**str_sep;

	str_sep = ft_split(str, ' ');
	status = 0;
	pid = fork();
	if (pid == -1)
	{
		g_error = errno;
        perror("Error: ");
	}
	else if (pid == 0)
		c_proccess(str, p);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_error = WEXITSTATUS(status);
}
