/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/05/11 10:39:38 by gromero-         ###   ########.fr       */
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
	{
		write(1, "\n", 1);
		g_error = 130;
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "  \n", 3);
		rl_on_new_line();
		rl_redisplay();
		g_error = 1;
	}
}

void	do_builtin(char *str, t_shell *p)
{
	if (!ft_strncmp(str, "pwd ", 4) || !ft_strncmp(str, "pwd", 3))
		do_pwd(p);
	else if (!ft_strncmp(str, "echo", 4))
		do_echo(str, p);
	else if (!ft_strncmp(str, "cd", ft_strlen(str)) || !ft_strncmp(str, "cd ",
			ft_strlen(str)))
		do_cd_home(p);
	else if (!ft_strncmp(str, "cd .", ft_strlen(str)))
		rl_on_new_line();
	else if (!ft_strncmp(str, "cd ", 3))
		do_cd(str, p);
	else if (!ft_strncmp(str, "exit", 4))
		do_exit(str, p);
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		do_env(p);
	else if (!ft_strncmp(str, "unset", 5))
		do_unset(p, str);
	else if (!ft_strncmp(str, "export", 6))
		do_export(str, p);
	else
		error_cmd(str);
}

int	check_builtin(char *str)
{
	if (!ft_strncmp(str, "pwd", 3))
		return (1);
	else if (!ft_strncmp(str, "cd", 2))
		return (1);
	else if (!ft_strncmp(str, "echo", 4))
		return (1);
	else if (!ft_strncmp(str, "exit", 4))
		return (1);
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "export", 6))
		return (1);
	else if (!ft_strncmp(str, "unset", 5))
		return (1);
	return (0);
}

void	free_executer(t_shell *p)
{
	int	i;

	i = 0;
	while (i < p->n_pipes)
	{
		free(p->pipes[i]->str);
		free(p->pipes[i]);
		i++;
	}
	free(p->pipes);
	free(p->str);
}

void	leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	int		i;
	t_shell	*p;

	//atexit(leaks);
	p = malloc(sizeof(t_shell));
	ft_init(envp, p);
	while (argc)
	{
		ft_init2(p);
		str = readline(BEGIN "minishell $ " CLOSE);
		if (!str)
			control_d();
		i = 0;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] == '\0')
			str = malloc(i * sizeof(char));
		if (str && *str)
			add_history(str);
		ft_init3(p, str, argv);
		free(str);
	}
	ft_free_env(p->var_env, p->env_n);
	free(p);
}
