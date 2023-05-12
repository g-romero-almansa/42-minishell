/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:22:12 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/11 12:22:15 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*exp_dollar(char *str, int j, t_shell *p, char **cpy)
{
	char	*sub;
	char	*temp;
	int		i;
	int		len;

	sub = ft_substr(str, j + 1, ft_strlen(str) - j - 1);
	i = 0;
	if (!ft_strncmp(sub, "$", 1))
	{
		free(sub);
		sub = ft_substr(str, j + 2, ft_strlen(str) - j - 2);
		len = ft_strlen(sub);
		temp = ft_strjoin(sub, "=");
		free(sub);
		while (i < p->env_n)
		{
			if (!ft_strncmp(temp, cpy[i], ft_strlen(temp)))
				sub = ft_substr(cpy[i], len + 1, ft_strlen(cpy[i]) - len - 1);
			i++;
		}
		free(temp);
	}
	return (sub);
}

int	var_exist(t_shell *p, char **cpy, char *sub)
{
	int	j;
	int	flag;

	flag = 0;
	j = -1;
	while (++j < p->env_n && cpy[j])
		if (!ft_strncmp(sub, cpy[j], ft_strlen(sub)))
			flag = 1;
	return (flag);
}

void	free_var(char *sub, char *prueba, char *temp)
{
	free(sub);
	free(prueba);
	free(temp);
}

void	exp_change(t_shell *p, char **cpy, char *sub, char *str)
{
	int		j;

	j = 0;
	while (j < p->env_n && cpy[j])
	{
		if (!ft_strncmp(sub, cpy[j], ft_strlen(sub)))
			p->var_env[j] = ft_strdup(str);
		else
			p->var_env[j] = ft_strdup(cpy[j]);
		j++;
	}
}

void	exp_add(t_shell *p, char **cpy, char *str)
{
	int	j;

	j = -1;
	while (++j < p->env_n && cpy[j])
		p->var_env[j] = ft_strdup(cpy[j]);
	p->var_env[j] = ft_strdup(str);
	p->env_n++;
}
