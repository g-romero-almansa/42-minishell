/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/02 10:54:19 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	sighandler(int num)
{
	if (num == SIGINT)
	{	
		rl_on_new_line();
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_replace_line("", 1);
		//rl_redisplay();
		//rl_replace_line("", 1);
	}
}

void	do_builtin(char *str, t_t *p)
{
    if (!ft_strncmp(str, "pwd", 3))
        do_pwd();
	else if (!ft_strncmp(str, "echo", 4))
        do_echo(str, p);
	else if (!ft_strncmp(str, "cd .", sizeof(str)))
        rl_on_new_line();
    else if (!ft_strncmp(str, "cd ", 3))
        do_cd(str);
    else if (!ft_strncmp(str, "cd", 2))
        do_cd_home();
	if (!ft_strncmp(str, "exit", sizeof(str)))
    {
        printf("exit\n");
        exit(0);
    }
    if (!ft_strncmp(str, "env", sizeof(str)))
        do_env(p);
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
    else if (!ft_strncmp(str, "exit", 4))
        return (1);
    else if (!ft_strncmp(str, "env", 3))
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
	t_t		*p;

	(void)argc;
    signal(SIGINT, sighandler);
    i = 0;
    while (envp[i])
        i++;
	var_env = (char **)malloc((i + 1) * sizeof(char *));
	if (!var_env)
		exit(0);
	p = malloc(sizeof(t_t));
	p->env_n = 28;
	p->flag_s = 0;
	p->flag_d = 0;
	p->flag_qu = 0;
    p->e_status = 0;
    var_env = ft_cpy_env(envp, var_env, p->env_n);
    while (1)
    {	
        str = readline(BEGIN "My Term $ " CLOSE);
		if (!str)
		{
            printf ("exit\n");
			exit(0);
		}
		ft_env_(str, var_env, p->env_n);
        if (str && *str)
            add_history(str);
        if (check_pipe(str))
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
