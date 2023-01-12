/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:13:23 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/27 12:24:50 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;

	i = ft_strlen(src);
	k = 0;
	if (!dst || !src)
		return (0);
	if (dstsize != 0)
	{
		while ((k < dstsize - 1) && src[k])
		{
			dst[k] = src[k];
			k++;
		}
		dst[k] = '\0';
	}
	return (i);
}
/*#include <stdio.h>
int main()
{
	char y[100];
	printf ("%zu", strlcpy(y, "Hollla", 11));
	printf ("%zu", ft_strlcpy(y, "hollla", 11));
}*/
