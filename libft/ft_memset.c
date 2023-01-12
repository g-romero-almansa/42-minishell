/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:38:14 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/21 12:47:45 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}
/*#include <stdio.h>
#include <string.h>
int main()
{
	char	y[20] = "Holaquetal";
	//printf ("%s\n", memset(y + 2, 36, 11));
	printf ("%s", ft_memset(y + 2, 36, 11));
}*/
