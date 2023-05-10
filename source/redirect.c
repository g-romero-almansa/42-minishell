/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:19:50 by gromero-          #+#    #+#             */
/*   Updated: 2023/05/03 13:12:41 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	do_redir(char *str, t_shell *p)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			double_input(str, p);
		else if (str[i] == '>' && str[i + 1] == '>')
			double_output(str, p);
		else if (str[i] == '<' && str[i - 1] != '<')
			input_redir(str, p);
		else if (str[i] == '>' && str[i - 1] != '>')
			output_redir(str, p);
		i++;
	}
}

int	check_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}
