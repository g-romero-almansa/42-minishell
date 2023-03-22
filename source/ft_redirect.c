/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:19:50 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/13 12:03:23 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_prueba(char *s, int flag)
{
	char	*ber;
	int 	i;
	int		j;
	int		fd;

	i = 0;
	if (flag == 1)
	{
		while (s[i] != '>')
			i++;
		ber = ft_strdup(&s[i + 2]);
		fd = open (ber, O_CREAT | O_WRONLY, S_IRWXU);
		j = 4;
		while (++j < i - 1)
			ft_putchar_fd(s[j], fd);
		ft_putchar_fd('\n', fd);
		close(fd);
		free (ber);
	}
	else if (flag == 2)
	{
		while (s[i] != '>')
			i++;
		i++;
		ber = ft_strdup(&s[i + 2]);
		printf ("%s\n", ber);
		fd = open (ber, O_APPEND | O_CREAT | O_WRONLY, S_IRWXU);
		j = 4;
		while (++j < i - 1)
			ft_putchar_fd(s[j], fd);
		ft_putchar_fd('\n', fd);
		close(fd);
		free (ber);
	}
}

