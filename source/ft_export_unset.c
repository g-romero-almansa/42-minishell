/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:13:42 by gromero-          #+#    #+#             */
/*   Updated: 2023/04/27 11:15:51 by gromero-         ###   ########.fr       */
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
		j = -1;
		while (++j < p->env_n && cpy[j])
			p->var_env[j] = ft_strdup(cpy[j]);
		p->var_env[j] = ft_strdup(str);
		p->env_n++;
	}
	return (p->var_env);
}

void	ft_show_export(t_shell *p)
{
	int		i;
	int		j;
	char	c;
	char	**tpm;

	j = -1;
	i = -1;
	c = 'A';
	tpm = (char **)malloc((p->env_n) * sizeof(char *));
	while (c <= 'Z')
	{
		j = -1;
		while (p->var_env[++j])
			if (p->var_env[j][0] == c)
				tpm[++i] = ft_substr(p->var_env[j], 0,
						ft_strlen(p->var_env[j]));
		c++;
	}
	j = -1;
	while (p->var_env[++j])
		if (p->var_env[j][0] == '_')
			tpm[++i] = ft_substr(p->var_env[j], 0, ft_strlen(p->var_env[j]));
	j = -1;
	c = 'a';
	while (c <= 'z')
	{
		j = -1;
		while (p->var_env[++j])
			if (p->var_env[j][0] == c)
				tpm[++i] = ft_substr(p->var_env[j], 0,
						ft_strlen(p->var_env[j]));
		c++;
	}
	j = -1;
	c = 34;
	while (++j < p->env_n)
	{
		i = -1;
		printf("declare -x ");
		while (tpm[j][++i])
		{
			printf("%c", tpm[j][i]);
			if (tpm[j][i] == '=' || tpm[j][i + 1] == '\0')
				printf("%c", c);
		}
		printf("\n");
	}
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
	}
	k = j + 1;
	while (k < p->env_n && cpy[k])
	{
		less = 1;
		p->var_env[j] = ft_strdup(cpy[k]);
		k++;
		j++;
	}
	if (less)
		p->env_n--;
	return (p->var_env);
}
