/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:21:48 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/26 14:10:27 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_echo(char *s, char **envp, int i)
{
	char	*p;
	int		j;

	p = malloc (1000 * sizeof(char));
	if (!p)
		exit (0);
	j = -1;
	while ((s[i] != ' ' || s[i] != '\t') && s[i])
		p[++j] = s[++i];
	p[j] = '\0';
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(p, envp[j], ft_strlen(p)))
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
