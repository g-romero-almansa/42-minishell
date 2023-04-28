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
	int		len;
	char	*pwd;

	len = ft_strlen(get_env("PWD", p));
	pwd = malloc(sizeof(char) * (len + 1));
	getcwd(pwd, len + 1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}

int	echo_status(int i)
{
	ft_putnbr_fd(g_error, 1);
	i++;
	g_error = 0;
	rl_on_new_line();
	return (i);
}

void	do_echo(char *str, t_shell *p)
{
	int	i;

	if (!ft_strncmp(str, "echo -n", 7))
		ft_putstr_fd(str + 8, 1);
	else if (!ft_strncmp(str, "echo", 4))
	{
		i = 4;
		if (str[i] != ' ')
		{
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": command not found", 2);
			g_error = 127;
		}
		else
		{
			while (str[++i])
			{
				//if (str[i] == 34 || str[i] == 39)
				//	i = ft_quotes(str, i, str[i], p);
				if (str[i] == '$' && str[i + 1] == '_')
				{
					echo_low_bar(str, p->var_env, p->env_n);
					i++;
				}
				else if (str[i] == '$' && str[i + 1] == '?')
					i = echo_status(i);
				else if (str[i] == '$' && p->interp)
					i = ft_echo(str, p->var_env, i) + i;
				else
					ft_putchar_fd(str[i], 1);
			}
			printf("\n");
		}
	}
}

void	do_unset(t_shell *p, char *str)
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
	p->var_env = (char **)malloc((p->env_n) * sizeof(char *));
	if (!p->var_env)
	{
		g_error = errno;
		perror("Error: ");
	}
	p->var_env = ft_unset(str + 6, cpy, p);
	ft_free_env(cpy, p->env_n + 1);
}

void	do_export(char *str, t_shell *p)
{
	char	**cpy;

	if (ft_strlen(str) == 6)
		ft_show_export(p);
	else
	{
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

void	do_exit(char *str)
{
	char	**arg;
	int		i;
	int		len;

	if (!ft_strncmp(str, "exit ", 5))
	{
		if (!ft_strncmp(str, "exit ", ft_strlen(str)))
		{
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		arg = ft_split(str, ' ');
		len = ft_strlen(arg[1]);
		i = 0;
		while (i < len)
		{
			if (!ft_isdigit(arg[1][i]))
			{
				free_matrix(arg);
				ft_putendl_fd("exit", 2);
				ft_putstr_fd(str, 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(0);
			}
			i++;
		}
		free_matrix(arg);
	}
	ft_putendl_fd("exit", 2);
	exit(0);
}
