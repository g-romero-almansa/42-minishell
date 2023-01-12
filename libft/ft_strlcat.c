/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:28:59 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/25 11:16:19 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	sol;
	int		i;

	len_dst = 0;
	len_src = 0;
	sol = 0;
	i = 0;
	while (dst[len_dst])
		len_dst++;
	while (src[len_src])
		len_src++;
	if (dstsize > len_dst)
		sol = len_dst + len_src;
	else
		sol = len_src + dstsize;
	while (src[i] && (len_dst + 1) < dstsize)
	{
		dst[len_dst] = src[i];
		len_dst++;
		i++;
	}
	dst[len_dst] = '\0';
	return (sol);
}
/*#include <stdio.h>
int main()
{
	char x[] = "Hola";
	char y[] = "Mundo";
	printf ("%zu", strlcat(x, y, 3));
	printf ("%zu", ft_strlcat(x, y, 3));
}*/
