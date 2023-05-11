/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:13:42 by gromero-          #+#    #+#             */
/*   Updated: 2023/05/11 11:17:45 by gromero-         ###   ########.fr       */
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
		ft_export2(p, cpy, sub, str);
	else
		ft_export3(p, cpy, str);
	free(sub);
	p->var_env[++j] = NULL;
	return (p->var_env);
}

void	ft_export2(t_shell *p, char **cpy, char *sub, char *str)
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

void	ft_export3(t_shell *p, char **cpy, char *str)
{
	int	j;

	j = -1;
	while (++j < p->env_n && cpy[j])
		p->var_env[j] = ft_strdup(cpy[j]);
	p->var_env[j] = ft_strdup(str);
	p->env_n++;
}

void	ft_show_export(t_shell *p)
{
	int		j;
	char	c;

	c = 64;
	while (++c <= 'Z')
	{
		j = -1;
		while (++j < p->env_n)
			if (p->var_env[j][0] == c)
				ft_show_export2(p, j);
	}
	j = -1;
	while (++j < p->env_n)
		if (p->var_env[j][0] == '_')
			ft_show_export2(p, j);
	c = 96;
	while (++c <= 'z')
	{
		j = -1;
		while (++j < p->env_n)
			if (p->var_env[j][0] == c)
				ft_show_export2(p, j);
	}
}

void	ft_show_export2(t_shell *p, int j)
{
	int		i;

	i = -1;
	printf("declare -x ");
	while (p->var_env[j][++i])
	{
		printf("%c", p->var_env[j][i]);
		if (p->var_env[j][i] == '=' || p->var_env[j][i + 1] == '\0')
			printf("\"");
	}
	printf("\n");
}

char	**ft_unset(char *str, char **cpy, t_shell *p)
{
	int		j;
	int		k;
	char	*s;
	int		less;

	s = ft_strjoin(str, "=");
	j = 0;
	less = 0;
	while (j < p->env_n && cpy[j] && ft_strncmp(s, cpy[j], ft_strlen(s)))
	{
		p->var_env[j] = ft_strdup(cpy[j]);
		j++;
		if (j != p->env_n && !ft_strncmp(s, cpy[j], ft_strlen(s)))
			less = 1;
	}
	k = j;
	j = ft_unset2(k, less, p, cpy);
	free(s);
	if (less)
		p->env_n--;
	p->var_env[j] = NULL;
	return (p->var_env);
}

int	ft_unset2(int k, int less, t_shell *p, char **cpy)
{
	int		j;

	j = k;
	while (++k < p->env_n && cpy[k])
	{
		less = 1;
		p->var_env[j++] = ft_strdup(cpy[k]);
	}
	return (j);
}
