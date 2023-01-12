/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:42:36 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/28 15:05:51 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{	
	char	*cpy;
	size_t	i;
	int		size;

	if (!s)
		return (0);
	if ((ft_strlen(s) - start) > len)
		size = len + 1;
	else
		size = ft_strlen(s) - start + 1;
	if (start >= ft_strlen(s))
		size = 1;
	cpy = (char *)malloc(size * sizeof(char));
	if (!cpy)
		return (0);
	i = 0;
	while ((size_t)start < ft_strlen(s) && i < len)
	{
		cpy[i] = s[start];
		start++;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
/*#include <stdio.h>
int main()
{
	printf ("%s", ft_substr("Hola Que Tal", 0, 10));
}*/
