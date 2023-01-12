/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:00:28 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/28 13:53:29 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((const char *)src)[i];
		i++;
	}
	return (dst);
}
/*#include <stdio.h>
#include <string.h>
int main()
{
	char x[25] = "A la primera";
	char y[40] = "Hey Que tal cabezon";
	//printf ("%s", ft_memcpy(x, y, 3));
	printf ("%s", memcpy(x, y, 3));
}*/
