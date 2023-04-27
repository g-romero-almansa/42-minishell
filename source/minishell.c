/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/04/27 10:17:36 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	sighandler(int num)
{
	pid_t	pid;
	int		status;

	(void)num;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == 0)
		write (1, "\n", 1);
	else
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write (1, "  \n", 3);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	do_builtin(char *str, t_shell *p)
{
    if (!ft_strncmp(str, "pwd", 3))
        do_pwd();
	else if (!ft_strncmp(str, "echo", 4))
        do_echo(str, p);
	else if (!ft_strncmp(str, "cd .", sizeof(str)))
        rl_on_new_line();
    else if (!ft_strncmp(str, "cd ", 3))
        do_cd(str, p);
    else if (!ft_strncmp(str, "cd", 2))
        do_cd_home(p);
	if (!ft_strncmp(str, "exit ", 5) || !ft_strncmp(str, "exit", 4))
        do_exit(str);
    if (!ft_strncmp(str, "env", sizeof(str)))
        do_env(p, str);
	if (!ft_strncmp(str, "unset", 5))
        do_unset(p, str);
    if (!ft_strncmp(str, "export", 6))
        do_export(str, p);
}

int check_builtin(char *str)
{
    if (!ft_strncmp(str, "pwd ", 4))
        return (1);
    else if (!ft_strncmp(str, "cd", 2))
        return (1);
    else if (!ft_strncmp(str, "echo ", 5))
        return (1);
    else if (!ft_strncmp(str, "exit ", 5) || !ft_strncmp(str, "exit", 4))
        return (1);
    else if (!ft_strncmp(str, "env", sizeof(str)))
        return (1);
    else if (!ft_strncmp(str, "export", 6))
        return (1);
    else if (!ft_strncmp(str, "unset", 5))
        return (1);
    return (0);
}

int	main(int argc, char **argv, char **envp)
{
    char    *str;
    int     i;
	t_shell *p;

	p = malloc(sizeof(t_shell));
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
    p->fd_out = STDOUT_FILENO;
    p->var_env = ft_cpy_env(envp, p->var_env, p->env_n);
	g_error = 0;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
    while (argc)
    {
        str = readline(BEGIN "minishell $ " CLOSE);
		if (!str)
		{
            ft_putstr_fd("exit\n", 2);
			exit(0);
		}
		ft_env_(str, p->var_env, p->env_n);
        if (str && *str)
            add_history(str);
        if (check_redir(str))
            do_redir(str, p);
        else if (check_pipe(str))
            do_pipes(str, p);
        else if (check_builtin(str))
            do_builtin(str, p);
        else if (check_exec(str))
            exec_file(str, argv, p);
        else
            find_cmd(str, p);	
        free(str);
    }
}
