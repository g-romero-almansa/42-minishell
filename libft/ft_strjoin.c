/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:53:40 by gromero-          #+#    #+#             */
/*   Updated: 2022/10/28 16:32:04 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ct;
	int		j;
	int		i;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ct = malloc((i + j) * sizeof(char));
	if (!ct)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ct[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ct[i] = s2[j];
		i++;
		j++;
	}
	ct[i] = '\0';
	return (ct);
}
