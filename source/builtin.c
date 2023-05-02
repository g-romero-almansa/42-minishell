/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:53:02 by barbizu-          #+#    #+#             */
/*   Updated: 2023/04/28 11:20:34 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	do_pwd(t_shell *p)
{
	char	*pwd;

	pwd = get_env("PWD=", p);
	ft_putendl_fd(pwd, 1);
}

void	do_unset(t_shell *p, char *str)
{
	char	**cpy;
	int		first_n;

	first_n = p->env_n;
	cpy = (char **)malloc((p->env_n + 1) * sizeof(char *));
	if (!cpy)
	{
		g_error = errno;
		perror("Error: ");
	}
	cpy = ft_cpy_env(p->var_env, cpy, p->env_n);
	ft_free_env(p->var_env, p->env_n);
	p->var_env = (char **)malloc((p->env_n + 1) * sizeof(char *));
	if (!p->var_env)
	{
		g_error = errno;
		perror("Error: ");
	}
	p->var_env = ft_unset(str + 6, cpy, p);
	if (first_n == p->env_n)
		ft_free_env(cpy, p->env_n);
	else
		ft_free_env(cpy, p->env_n + 1);
}

void	export_cnt(t_shell *p, char *str)
{
	char	**cpy;

	cpy = (char **)malloc((p->env_n + 1) * sizeof(char *));
	if (!cpy)
	{
		g_error = errno;
		perror("Error: ");
	}
	cpy = ft_cpy_env(p->var_env, cpy, p->env_n);
	ft_free_env(p->var_env, p->env_n);
	p->var_env = (char **)malloc((p->env_n + 2) * sizeof(char *));
	if (!p->var_env)
	{
		g_error = errno;
		perror("Error: ");
	}
	p->var_env = ft_export(str + 7, cpy, p);
	ft_free_env(cpy, p->env_n - 1);
}

void	do_export(char *str, t_shell *p)
{
	if (!ft_strncmp(str, "export", ft_strlen(str)) || !ft_strncmp(str,
			"export ", ft_strlen(str)))
		ft_show_export(p);
	else if (!ft_strncmp(str, "export ", 7))
		export_cnt(p, str);
	else
		error_cmd(str);
}

void	do_env(t_shell *p)
{
	int	i;

	i = 0;
	while (i < p->env_n && p->var_env[i])
	{
		ft_putendl_fd(p->var_env[i], 1);
		i++;
	}
}
