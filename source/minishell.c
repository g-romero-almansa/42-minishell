/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/08 12:14:43 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	sighandler(int num)
{
	if (num == SIGINT)
	{	
		rl_on_new_line();
		printf ("\n");
		rl_redisplay();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	do_cmd(char *str, t_t *p)
{
    char	*pwd;
    char	*s;
    char	*dir;
    char	*path_dir;
	int		i;
	int		j;
	int		len;

    len = 0;
    if (!ft_strncmp(str, "pwd", 3))
    {
		len = ft_strlen(getenv("PWD"));
		pwd = malloc(sizeof(char) * (len + 1));
		getcwd(pwd, len + 1);
		printf("%s\n", pwd);
		rl_on_new_line();
	}
	else if (!ft_strncmp(str, "echo -n", 7))
	{
		printf("%s", str + 8);
		rl_on_new_line();
	}
	else if (!ft_strncmp(str, "echo", 4))
	{
		i = 4;
		while (str[++i])
        {
            if (str[i] == '$' && str[i + 1] == '_')
            {
                echo_low_bar(str, var_env);
                i++;
            }
            else if (str[i] == '$')
				i = ft_echo(str, var_env, i) + i;
            else
				printf ("%c", str[i]);
        }
        printf("\n");
		rl_on_new_line();
	}
	else if (!ft_strncmp(str, "cd .", sizeof(str)))
        rl_on_new_line();
    else if (!ft_strncmp(str, "cd ", 3))
    { 
        if (!ft_strncmp(str, "cd ..", sizeof(str)))
        {
			pwd = malloc(sizeof(char) * ft_strlen(getenv("PWD")));
			getcwd(pwd, ft_strlen(getenv("PWD")));
            chdir("..");
			s = malloc (sizeof(char) * ft_strlen(getenv("PWD")));
			getcwd(s, ft_strlen(getenv("PWD")));
			ft_env_pwd(pwd, s, var_env, 1);
            rl_on_new_line();
        }
        else if (!ft_strncmp(str, "cd ", sizeof(str)))
        {
            pwd = malloc(sizeof(char) * ft_strlen(getenv("PWD")));
            getcwd(pwd, ft_strlen(getenv("PWD")));	
 			len = ft_strlen(getenv("HOME"));
            s = malloc(sizeof(char) * len);
            s = getenv("HOME");
			ft_env_pwd(pwd, s, var_env, 1);
            chdir(s);
        }
        else
        {
            dir = malloc(sizeof(char) * (ft_strlen(str) - 3));
            dir = ft_strchr(str, ' ');
            if (dir[1] != '/')
            {
                dir[0] = '/';
                len = ft_strlen(getenv("PWD"));
                pwd = malloc(sizeof(char) * (len + 1));
                getcwd(pwd, len + 1);
                path_dir = ft_strjoin(pwd, dir);
				ft_env_pwd(pwd, path_dir, var_env, 1);
				chdir(path_dir);
            }
            else
            {
				pwd = malloc(sizeof(char) * ft_strlen(getenv("PWD")));
				getcwd(pwd, ft_strlen(getenv("PWD")));
                dir = ft_strchr(str, '/');
				ft_env_pwd(pwd, dir, var_env, 1);
                chdir(dir);
            }
        }
    }
    else if (!ft_strncmp(str, "cd", 2))
    {
        len = ft_strlen(getenv("HOME"));
        s = malloc(sizeof(char) * len);
        s = getenv("HOME");
		ft_env_pwd(getenv("PWD"), s, var_env, 1);
        chdir(s);
    }
	if (!ft_strncmp(str, "exit", sizeof(str)))
    {
			printf("exit\n");
            exit (0);
    }
    if (!ft_strncmp(str, "env", sizeof(str)))
	{
		j = -1;
		while (++j <= (p->env_n))
			printf ("%s\n", var_env[j]);
	}
	if (!ft_strncmp(str, "unset", 5))
	{
		char	**cpy;

		cpy = (char **)malloc((p->env_n) * sizeof(char *));
		cpy = ft_cpy_env(var_env, cpy, p->env_n);
		ft_free_env (var_env, p->env_n);
		var_env = (char **)malloc((p->env_n - 1) * sizeof(char *));
		var_env = ft_unset(str + 6, cpy, p->env_n);
		ft_free_env(cpy, p->env_n);
		i = -1;
		while (++i < p->env_n)
			printf ("%s\n", var_env[i]);
		p->env_n--;
    }
    if (!ft_strncmp(str, "export", 6))
    {
		char	**cpy;

		cpy = (char **)malloc((p->env_n) * sizeof(char *));
		cpy = ft_cpy_env(var_env, cpy, p->env_n);
		ft_free_env (var_env, p->env_n);
		var_env = (char **)malloc((p->env_n + 1) * sizeof(char *));
		var_env = ft_export(str + 7, cpy, p->env_n);
		ft_free_env (cpy, p->env_n);
		p->env_n++;
    }
}

int check_builtin(char *str)
{
    if (!ft_strncmp(str, "pwd", 3))
        return (1);
    else if (!ft_strncmp(str, "cd", 2))
        return (1);
    else if (!ft_strncmp(str, "echo", 4))
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
	int		i;
	t_t		*p;

	(void)argc;
    (void)argv;
    signal(SIGINT, sighandler);
	i = 0;
	while (envp[i])
		i++;
	var_env = (char **)malloc((i + 1) * sizeof(char *));
	p = malloc(sizeof(t_t));
	p->env_n = 28;
	if (!var_env)
		exit(0);
    var_env = ft_cpy_env(envp, var_env, p->env_n);
    while (1)
    {	
        str = readline(BEGIN "My Term $ " CLOSE);
		if (!str)
		{
            printf ("exit\n");
			exit(0);
		}
		ft_env_(str, var_env);
        if (str && *str)
            add_history(str);
        if (check_pipe(str))
            do_pipes(str);
        else if (check_builtin(str))
            do_cmd(str, p);
        else
            find_cmd(str, var_env, argv);
        free(str);
    }
}
