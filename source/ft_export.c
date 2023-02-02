/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:13:42 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/31 12:00:41 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	**ft_export(char **envp, char *str, int i, char **cpy)
{
	char	*acum;
	int		j;
	int		k;

	cpy = (char **)malloc((i + 1) * sizeof(char *));
	acum = (char *)malloc(ft_strlen(envp[i - 1]) * sizeof(char));
	if (!cpy || !acum)
		exit(0);
	acum = envp[i - 1];
	j = -1;
	while (++j < (i - 1))
	{
		cpy[j] = (char *)malloc(ft_strlen(envp[j]) * sizeof(char));
		k = -1;
		while (envp[j][++k])
			cpy[j][k] = envp[j][k];
		free(envp[j]);
	}
	cpy[j] = (char *)malloc(ft_strlen(str) * sizeof(char));
	j = 0;
	while (str[j] != ' ')
		j++;
	k = -1;
	while (str[++j])
	{	
		cpy[i - 1][++k] = str[j];
	}
	cpy[i] = (char *)malloc(ft_strlen(envp[i - 1]) * sizeof(char));
	j = -1;
	while (envp[i - 1][++j])
		cpy[i][j] = envp[i - 1][j];
	free(envp[i - 1]);
	free(envp);
	cpy[++i] = (char *)malloc(1 * sizeof(char));
	cpy[i][0] = '\0';
	return (cpy);
}
