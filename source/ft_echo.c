/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:21:48 by gromero-          #+#    #+#             */
/*   Updated: 2023/05/10 10:26:57 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	search_echo(char *p, char **envp, int max)
{
	int	j;
	int	i;

	j = 0;
	while (j < max)
	{
		if (!ft_strncmp(p, envp[j], ft_strlen(p))
			&& (ft_strlen(p) == ft_count(envp[j])))
		{
			i = -1;
			while (envp[j][i] != '=')
				i++;
			while (envp[j][++i])
				ft_putchar_fd(envp[j][i], 1);
		}
		j++;
	}
}

int	ft_echo(char *s, char **envp, int i, int max)
{
	char	*p;
	int		j;

	p = malloc((ft_strlen(s) - 5) * sizeof(char));
	if (!p)
		std_error();
	j = -1;
	while (s[i] != ' ' && s[i] && s[i] != 34 && s[i] != 39)
		p[++j] = s[++i];
	p[j] = '\0';
	search_echo(p, envp, max);
	j = ft_strlen(p);
	free(p);
	return (j);
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
		if (!s)
		{
			std_error();
			exit(errno);
		}
		s = ft_strchr(envp[i], '=');
		if (!ft_strncmp(envp[i], "_=$", 3))
		{
			s = ft_strchr(envp[i], '$');
			s = ft_strjoin("echo ", s);
			ft_echo(s, envp, 5, max);
		}
		else
			ft_putstr_fd(s + 1, 1);
	}
}
