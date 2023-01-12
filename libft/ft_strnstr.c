/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:31:55 by gromero-          #+#    #+#             */
/*   Updated: 2022/04/27 12:44:06 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_needle;

	i = 0;
	j = 0;
	len_needle = ft_strlen(needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		if (haystack[i] == needle[j])
		{
			while (needle[j] == haystack[i + j] && needle[j] && (i + j < len))
			{
				j++;
			}
			if (j == len_needle)
				return (&((char *)haystack)[i]);
			else
				j = 0;
		}
		i++;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>
int main()
{
	char * empty = (char*)"";

	printf ("%s\n", strnstr(empty, "", 0));
	printf ("%s", ft_strnstr(empty, "", 0));
}*/
