/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:36:57 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/28 14:40:26 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if ((count == SIZE_MAX && size > 1) || (size == SIZE_MAX && count > 1))
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
/*#include <stdio.h>
int main()
{
	printf ("%s", ft_calloc(SIZE_MAX , SIZE_MAX));
//	printf ("%s", calloc(SIZE_MAX, SIZE_MAX));
}*/
