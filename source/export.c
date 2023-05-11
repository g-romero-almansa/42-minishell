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

char	**ft_export(char *str, char **cpy, t_shell *p)
{
	int		j;
	char	*sub;
	int		flag;

	j = 0;
	flag = 0;
	while (str[j] != '=')
		j++;
	sub = ft_substr(str, 0, j + 1);
	j = -1;
	while (++j < p->env_n && cpy[j])
		if (!ft_strncmp(sub, cpy[j], ft_strlen(sub)))
			flag = 1;
	if (flag == 1)
		exp_remove(p, cpy, sub, str);
	else
		exp_change(p, cpy, str);
	free(sub);
	p->var_env[++j] = NULL;
	return (p->var_env);
}

void	exp_remove(t_shell *p, char **cpy, char *sub, char *str)
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

void	exp_change(t_shell *p, char **cpy, char *str)
{
	int	j;

	j = -1;
	while (++j < p->env_n && cpy[j])
		p->var_env[j] = ft_strdup(cpy[j]);
	p->var_env[j] = ft_strdup(str);
	p->env_n++;
}
