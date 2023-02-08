/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:13:42 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/07 13:06:36 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char 	**ft_export(char *str, char **cpy, int i)
{
	int		j;
	char	*acum;

	acum = cpy[i];
	j = -1;
	while (++j < i)
		var_env[j] = ft_strdup(cpy[j]);
	var_env[j] = ft_strdup(str);
	var_env[++j] = ft_strdup(acum);
	return (var_env);
}
