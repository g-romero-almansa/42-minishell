/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:13:42 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/01 12:22:10 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_export(char *str, int i)
{
	char	**cpy;
	int		j;
	int		k;

	cpy = (char **)malloc((i + 1) * sizeof(char *));
	if (!cpy)
		exit(0);
	cpy = ft_cpy_env2(var_env, cpy);
	ft_free_env(var_env);
	var_env = (char **)malloc((i + 100) * sizeof(char *));
	j = -1;
	while (++j < (i - 1))
	{
		var_env[j] = (char *)malloc(ft_strlen(cpy[j]) * sizeof(char));
		k = -1;
		while (cpy[j][++k])
			var_env[j][k] = cpy[j][k];
	}
	var_env[j] = (char *)malloc((ft_strlen(str) - 7) * sizeof(char));
	k = -1;
	while (str[++k + 7])
	{
		var_env[j][k] = str[k + 7];
	}
	var_env[++j] = (char *)malloc(ft_strlen(cpy[i - 1] + 10) * sizeof(char));
	k = -1;
	while (cpy[i - 1][++k])
		var_env[j][k] = cpy[i - 1][k];
	ft_free_env(cpy);
}
