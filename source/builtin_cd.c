/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:35:45 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/03 13:06:03 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*get_env(char *s, t_shell *p)
{
	int	i;

	i = 0;
	while (i < p->env_n)
	{
		if (!ft_strncmp(p->var_env[i], s, ft_strlen(s)))
			return (p->var_env[i] + ft_strlen(s));
		i++;
	}
	return (NULL);
}

void	do_cd_back(t_shell *p)
{
	char	*s;

	chdir("..");
	s = malloc(sizeof(char) * ft_strlen(get_env("PWD=", p)));
	if (!s)
	{
		g_error = errno;
		perror("Error: ");
	}
	getcwd(s, ft_strlen(get_env("PWD=", p)));
	ft_env_pwd(get_env("PWD=", p), s, p->var_env);
	rl_on_new_line();
	free(s);
}

void	do_cd_home(t_shell *p)
{
	char	*s;
	int		len;

	len = ft_strlen(get_env("HOME=", p));
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
	{
		g_error = errno;
		perror("Error: ");
	}
	s = get_env("HOME=", p);
	ft_env_pwd(get_env("PWD=", p), s, p->var_env);
	chdir(s);
}

void	open_dir(char *path_dir, char *str, t_shell *p)
{
	DIR		*dirp;

	dirp = opendir(path_dir);
	path_dir[ft_strlen(path_dir) - 1] = '\0';
	if (dirp == NULL)
	{
		g_error = 1;
		printf("%s: %s\n", str, strerror(errno));
	}
	else
	{
		ft_env_pwd(get_env("PWD=", p), path_dir, p->var_env);
		chdir(path_dir);
		closedir(dirp);
	}
}

void	do_cd(char *str, t_shell *p)
{
	char	*dir;
	char	*pwd;
	int		len;
	char	*path_dir;

	if (!ft_strncmp(str, "cd ..", ft_strlen(str)))
		do_cd_back(p);
	else
	{
		dir = malloc(sizeof(char) * (ft_strlen(str) - 3));
		if (!dir)
			error_malloc();
		dir = ft_strchr(str, ' ');
		dir[0] = '/';
		len = ft_strlen(get_env("PWD=", p));
		pwd = get_env("PWD=", p);
		path_dir = ft_strjoin(pwd, dir);
		open_dir(path_dir, str, p);
		free(path_dir);
	}
}
