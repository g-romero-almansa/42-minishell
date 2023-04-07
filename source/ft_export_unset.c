/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:13:42 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/02 11:02:53 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char 	**ft_export(char *str, char **cpy, t_shell *p)
{
	int		j;
	char	*sub;
	int		flag;

	j = 0;
	flag = 0;
	while (str[j] != '=')
		j++;
	sub = ft_substr(str, 0, j);
	if (!ft_strncmp(sub, "PATH", ft_strlen(sub)))
	{
		p->var_env = ft_unset(sub, cpy, p);
		free(sub);
	}
	else
	{
		j = 0;
		while (j < p->env_n && cpy[j])
		{
			if (!ft_strncmp(sub, cpy[j], ft_strlen(sub)))
				flag = 1;
			j++;
		}
		if (flag == 1)
		{
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
		else
		{
			p->env_n++;
			j = -1;
			while (++j < p->env_n && cpy[j])
				p->var_env[j] = ft_strdup(cpy[j]);
			p->var_env[j] = ft_strdup(str);
		}
		free(sub);
	}
	return (p->var_env);
}

char	**ft_unset(char *str, char **cpy, t_shell *p)
{
	int		j;
	int		k;
	char	*s;

	s = ft_strjoin(str, "=");
	j = 0;
	while (j < p->env_n && cpy[j] && ft_strncmp(s, cpy[j], ft_strlen(s)))
	{
		p->var_env[j] = ft_strdup(cpy[j]);
		j++;
	}
	k = j + 1;
	while (k < p->env_n && cpy[k])
	{
		p->var_env[j] = ft_strdup(cpy[k]);
		k++;
		j++;
	}
	p->env_n--;
	return (p->var_env);
}
