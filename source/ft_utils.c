/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:35:18 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/07 13:06:55 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*ft_last_word(char *s)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(ft_strlen(s) * sizeof(char));
	i = ft_strlen(s) - 1;
	while (s[i] != ' ' && s[i] != '\t' && s[i])
		i--;
	j = -1;
	while (s[++i])
		str[++j] = s[i];
	str[j + 1] = '\0';
	return (str);
}

void	ft_free_env(char **env, int j)
{
	int		i;
	
	i = -1;
	while (++i < j && env[i])
		free(env[i]);
	free(env);
}
