/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:33:16 by barbizu-          #+#    #+#             */
/*   Updated: 2023/04/27 12:33:20 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	executer(t_shell *p, char *str, char **argv)
{
	int	i;

	i = 0;
	if (p->n_pipes == 0)
	{
		if (check_redir(str))
			do_redir(str, p);
		else if (check_builtin(str))
			do_builtin(str, p);
		else if (check_exec(str))
			exec_file(argv, p);
		else
			find_cmd(p);
	}
	else
		do_pipes(p->str, p);
}
