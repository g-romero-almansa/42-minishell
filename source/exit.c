/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:20:20 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/02 13:20:24 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	exit_num(t_shell *p, char *str)
{
	char	**arg;
	int		i;
	int		len;

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
			free_exit(p, str);
			exit(0);
		}
		i++;
	}
	free_matrix(arg);
	free_exit(p, str);
	ft_putendl_fd("exit", 2);
	exit(0);
}

void	do_exit(char *str, t_shell *p)
{
	if (!ft_strncmp(str, "exit ", 5))
	{
		if (!ft_strncmp(str, "exit ", ft_strlen(str)))
		{
			free_exit(p, str);
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		exit_num(p, str);
	}
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
	{
		free_exit(p, str);
		ft_putendl_fd("exit", 2);
		exit(0);
	}
	else
		error_cmd(str);
}

void	free_exit(t_shell *p, char *str)
{
	int	i;

	free(str);
	free(p->str);
	ft_free_env(p->var_env, p->env_n);
	i = 0;
	while (i < p->n_tokens)
	{
		free(p->tokens[i]->value);
		free(p->tokens[i]);
		i++;
	}
	free(p->tokens);
	i = 0;
	while (i <= p->n_pipes)
	{
		free(p->pipes[i]->str);
		free(p->pipes[i]);
		i++;
	}
	free(p->pipes);
	free(p);
}
