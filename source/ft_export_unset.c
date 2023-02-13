/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:13:42 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/08 12:52:08 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char 	**ft_export(char *str, char **cpy, int i)
{
	int		j;

	j = -1;
	while (++j <= i)
		var_env[j] = ft_strdup(cpy[j]);
	var_env[j] = ft_strdup(str);
	return (var_env);
}

char	**ft_unset(char *str, char **cpy, int i)
{
	int		j;
	int		k;

	j = 0;
	while (j <= i && ft_strncmp(str, cpy[j], ft_strlen(str)))
	{
		var_env[j] = ft_strdup(cpy[j]);
		j++;
	}
	k = j + 1;
	while (k <= i)
	{
		var_env[j] = ft_strdup(cpy[k]);
		k++;
	}
	return (var_env);
}
