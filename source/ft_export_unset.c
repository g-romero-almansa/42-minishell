/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:13:42 by gromero-          #+#    #+#             */
/*   Updated: 2023/04/10 10:53:39 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char 	**ft_export(char *str, char **cpy, int i)
{
	int		j;

	j = -1;
	while (++j <= i && cpy[j])
		var_env[j] = ft_strdup(cpy[j]);
	var_env[j] = ft_strdup(str);
	return (var_env);
}

void	ft_show_export(t_t *p)
{
	int		i;
	int		j;
	int		n_env;
	char	**s;

	n_env = p->env_n;
	s = (char **)malloc((n_env + 1) * sizeof(char *));
	j = -1;
	i = ft_searchbigger(p);
	while (i != -1)
	{
		/*printf ("declare - x ");
		j = -1;
		while (var_env[i][++j])
		{
			printf ("%c", var_env[i][j]);
			if (var_env[i][j] == '=' || var_env[i][j + 1] == '\0')
				printf ("%c", 34);
		}
		printf ("\n");*/
		s[++j] = ft_strdup(var_env[i]);
		n_env--;
		i = ft_searchbigger(p);
	}
	i = ft_searchbigger3(p);
	while (i != -1)
	{
		/*printf ("declare - x ");
		j = -1;
		while (var_env[i][++j])
		{
			printf ("%c", var_env[i][j]);
			if (var_env[i][j] == '=' || var_env[i][j + 1] == '\0')
				printf ("%c", 34);
		}
		printf ("\n");*/
		s[++j] = ft_strdup(var_env[i]);
		n_env--;
		i = ft_searchbigger3(p);
	}
	i = ft_searchbigger2(p);
	while  (i != -1)
	{
		/*printf ("declare - x ");
		j = -1;
		while (var_env[i][++j])
		{
			printf ("%c", var_env[i][j]);
			if (var_env[i][j] == '=' || var_env[i][j + 1] == '\0')
				printf ("%c", 34);
		}
		printf ("\n");*/
		s[++j] = ft_strdup(var_env[i]);
		n_env--;
		i = ft_searchbigger2(p);
	}
	//s = ft_order(s, p->env_n);	
}

int	ft_searchbigger(t_t *p)
{
	static int	i = -1;
	static char	c = 'A';

	while (c <= 'Z')
	{
		while (++i <= p->env_n)
			if (var_env[i][0] == c)
				return (i);
		i = -1;
		c++;
	}
	i = -1;
	c = 'A';
	return (-1);
}

int	ft_searchbigger2(t_t *p)
{
	static int	i = -1;
	static char	c = 'a';

	while (c <= 'z')
	{
		while (++i <= p->env_n)
			if (var_env[i][0] == c)
				return (i);
		i = -1;
		c++;
	}
	i = -1;
	c = 'a';
	return (-1);
}

int	ft_searchbigger3(t_t *p)
{
	static int	i = -1;

	while (++i <= p->env_n)
	{
		if (var_env[i][0] == '_')
			return (i);
	}
	i = -1;
	return (-1);
}

char	**ft_unset(char *str, char **cpy, int i)
{
	int		j;
	int		k;
	char	*s;

	s = ft_strjoin(str, "=");
	j = 0;
	while (j <= i && ft_strncmp(s, cpy[j], ft_strlen(s)))
	{
		var_env[j] = ft_strdup(cpy[j]);
		j++;
	}
	k = j + 1;
	while (k <= i)
	{
		var_env[j] = ft_strdup(cpy[k]);
		k++;
		j++;
	}
	return (var_env);
}
