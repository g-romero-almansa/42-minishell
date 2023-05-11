/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:24:18 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/03 13:06:32 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	echo_status(int i)
{
	ft_putnbr_fd(g_error, 1);
	i++;
	g_error = 0;
	rl_on_new_line();
	return (i);
}

void	print_echo(char *str, t_shell *p)
{
	int	i;

	i = 4;
	if (str[i] != ' ')
		error_cmd(str);
	else
	{
		while (str[++i])
		{
			if (str[i] == '$' && str[i + 1] == '_')
			{
				echo_low_bar(str, p->var_env, p->env_n);
				i++;
			}
			else if (str[i] == '$' && str[i + 1] == '?')
				i = echo_status(i);
			else if (str[i] == '$' && p->interp)
				i = ft_echo(str, p->var_env, i, p->env_n) + i;
			else
				ft_putchar_fd(str[i], 1);
		}
		printf("\n");
	}
}

void	do_echo(char *str, t_shell *p)
{
	if (!ft_strncmp(str, "echo -n", 7))
		ft_putstr_fd(str + 8, 1);
	else if (!ft_strncmp(str, "echo", 4))
	{
		if (!ft_strncmp(str, "echo", ft_strlen(str)))
			printf("\n");
		else
			print_echo(str, p);
	}
}
