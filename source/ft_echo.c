/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:21:48 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/20 12:37:07 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_echo(char *s, char **envp, int i)
{
	char	*p;
	int		j;

	p = malloc((ft_strlen(s) - 6) * sizeof(char));
	if (!p)
		exit (0);
	j = -1;
	while (s[i] != ' ' && s[i])
		p[++j] = s[++i];
	p[j] = '\0';
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(p, envp[j], ft_strlen(p)) && ft_strlen(p) == ft_count(envp[j]))
		{
			i = -1;	
			while (envp[j][i] != '=')
				i++;
			while (envp[j][++i])
				printf ("%c", envp[j][i]);
		}
	}
	return (ft_strlen(p));
}

size_t	ft_count(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

void	echo_low_bar(char *str, char **envp, int max)
{
	int		i;
	char	*s;

	i = 0;
	if (!ft_strncmp(str, "echo $_", ft_strlen(str)))
	{
		while (i < max && ft_strncmp(envp[i], "_=", 2))
			i++;
		s = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		s = ft_strchr(envp[i], '=');
		if (!ft_strncmp(envp[i], "_=$", 3))
		{
			s = ft_strchr(envp[i], '$');
			s = ft_strjoin("echo ", s);
			ft_echo(s, envp, 5);
		}
		else
			printf("%s", s + 1);
	}
}

int	ft_quotes(char *s, int i, char c, t_t *p)
{
	int		j;

	p->flag_qu = 0;
	j = i;
	++i;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	if (i != (int)ft_strlen(s) && c == 34)
		p->flag_qu = 1;
	else if (c == 34)
		write (1, &c, 1);
	 if (i != (int)ft_strlen(s) && c == 39)
		p->flag_qu = 2;
	 else if (c == 39)
		 write (1, &c, 1);
	if (p->flag_qu == 2)
		while (++j < i)
			write (1, &s[j], 1);
	if (p->flag_qu == 1)
		while (++j < i)
		{
			if (s[j] == '$' && s[j + 1] == '_')
            {
                echo_low_bar(s, var_env);
                j++;
            }
            else if (s[j] == '$')
			{
				j = ft_echo(s, var_env, j) + j;
			}
			else
				printf ("%c", s[j]);
		}
	return (j);
}
