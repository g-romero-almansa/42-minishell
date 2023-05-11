/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:08:55 by gromero-          #+#    #+#             */
/*   Updated: 2023/05/11 13:24:08 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_init(char **envp, t_shell *p)
{
	int		i;
	struct sigaction sa;

	i = 0;
	while (envp[i])
		i++;
	p->var_env = (char **)malloc((i + 1) * sizeof(char *));
	if (!p->var_env)
		exit(0);
	p->env_n = i;
	p->flag_s = 0;
	p->flag_d = 0;
	p->flag_qu = 0;
	p->var_env = ft_cpy_env(envp, p->var_env, p->env_n);
	g_error = 0;
	rl_catch_signals = 0;
	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = sighandler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_init2(t_shell *p)
{
	p->interp = 1;
	p->append = 0;
	p->n_pipes = 0;
	p->fd_out = STDOUT_FILENO;
	p->fd_in = STDIN_FILENO;
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}

void	ft_init3(t_shell *p, char *str, char **argv)
{	
	if (str && *str)
		add_history(str);
	if (ft_strlen(str) != 0)
	{
		ft_env_(str, p->var_env, p->env_n);
		p->str = ft_strdup(str);
		lexer(str, p);
		parser(p);
		free_tokens(p);
		executer(p, str, argv);
		free_executer(p);
	}
}

void	control_d(void)
{
	ft_putstr_fd("exit\n", 2);
	exit(0);
}
