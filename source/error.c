/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:22:36 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/02 13:22:38 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	error_cmd(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	g_error = 127;
}

void	std_error(void)
{
	g_error = errno;
	perror("Error: ");
}

void	error_nofile(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
	g_error = 127;
}
