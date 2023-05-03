/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:53:02 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/03 10:54:55 by gromero-         ###   ########.fr       */
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
	if (!ft_strncmp(str, "echo", 5) && ft_strlen(str) == 4)
		printf ("\n");
	else if (!ft_strncmp(str, "echo -n", 7))
		ft_putstr_fd(str + 8, 1);
	else if (!ft_strncmp(str, "echo", 4))
		do_unset2(p->env_n, p, str);
}

void	do_unset2(int first_n, t_shell *p, char *str)
{
	char	**cpy;

	//first_n = p->env_n;
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
