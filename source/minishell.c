/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/12 12:52:14 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	sighandler(int signum)
{
	signum = 0;
	//write (1, "\n", 1);
	rl_on_new_line;
	//exit (1);
}
int	main(void)
{
	char	*str;
	int		pid;

	pid = getpid();
	printf ("%d", pid);
	signal (SIGINT, sighandler);
	while (1)
	{
		str = readline("gromero-42 $ ");
		add_history(str);
		free (str);
	}
	return (0);
}
