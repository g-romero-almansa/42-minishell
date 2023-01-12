/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:01:59 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/28 14:03:39 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((char *)s)[i] == (char)c)
			return (&((void *)s)[i]);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>
int main()
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};

	printf ("%s\n", memchr("s", 2, 3));
	printf ("%s", ft_memchr("s", 2, 3));
}*/
