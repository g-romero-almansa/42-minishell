/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:21:48 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/23 11:52:27 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_echo(char *s, char **envp, int i)
{
	char	*p;
	int		j;

	p = malloc((ft_strlen(s) - 6) * sizeof(char));
	if (!p)
	{
		g_error = errno;
		perror("Error: ");
		exit(errno);
	}
	j = -1;
	while (s[i] != ' ' && s[i] && s[i] != 34 && s[i] != 39)
		p[++j] = s[++i];
	p[j] = '\0';
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(p, envp[j], ft_strlen(p)) && (ft_strlen(p) == ft_count(envp[j])))
		{
			i = -1;
			while (envp[j][i] != '=')
				i++;
			while (envp[j][++i])
				ft_putchar_fd(envp[j][i], 1);
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
		if (!s)
		{
			g_error = errno;
			perror("Error: ");
			exit(errno);
		}
		s = ft_strchr(envp[i], '=');
		if (!ft_strncmp(envp[i], "_=$", 3))
		{
			s = ft_strchr(envp[i], '$');
			s = ft_strjoin("echo ", s);
			ft_echo(s, envp, 5);
		}
		else
			ft_putstr_fd(s + 1, 1);
	}
}

int	ft_quotes(char *s, int i, char c, t_shell *p)
{
	int		j;

	p->flag_qu = 0;
	j = i;
	++i;
	while (s[i])
		i++;
	while (s[i] != c)
		i--;
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
                echo_low_bar(s, p->var_env, p->env_n);
                j++;
            }
            else if (s[j] == '$')
			{
				j = ft_echo(s, p->var_env, j) + j;
			}
			else if (s[j] != 34)
				printf ("%c", s[j]);
		}
	return (j);
}
