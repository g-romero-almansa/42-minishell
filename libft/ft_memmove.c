/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:11:18 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/27 11:40:09 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		i = len - 1;
		while (i >= 0 && i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}
/*#include <stdio.h>
#include <string.h>
int main()
{
	char	x[30] = "A la primera Crac de Cracks";
	char	y[50] = "Hey Que tal cabezon";
	char sResult[] = {67, 68, 67, 68, 69, 0, 45};
	char sResult2[] = {67, 67, 68, 68, 69, 0, 45};

	printf ("%s\n", memmove(x, y, 5));
	//printf ("%s", memmove(sResult + 1, sResult, 2));
	//printf ("%s", ft_memmove(sResult + 1, sResult, 2));
	printf ("%s", ft_memmove(x , y, 15));
}*/
