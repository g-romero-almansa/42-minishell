/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/30 10:31:50 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	sighandler(int num)
{
	if (num == SIGINT)
	{
		printf ("\n");
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	do_cmd(char *str, char **envp)
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
			if (str[i] == '$')
				i = ft_echo(str, envp, i) + i;
			else
				printf ("%c", str[i]);
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
			ft_env_pwd(pwd, s, envp, 1);
            rl_on_new_line();
        }
        else if (!ft_strncmp(str, "cd ", sizeof(str)))
        {
            pwd = malloc(sizeof(char) * ft_strlen(getenv("PWD")));
            getcwd(pwd, ft_strlen(getenv("PWD")));	
 			len = ft_strlen(getenv("HOME"));
            s = malloc(sizeof(char) * len);
            s = getenv("HOME");
			ft_env_pwd(pwd, s, envp, 1);
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
				ft_env_pwd(pwd, path_dir, envp, 1);
				chdir(path_dir);
            }
            else
            {
				pwd = malloc(sizeof(char) * ft_strlen(getenv("PWD")));
				getcwd(pwd, ft_strlen(getenv("PWD")));
                dir = ft_strchr(str, '/');
				ft_env_pwd(pwd, dir, envp, 1);
                chdir(dir);
            }
        }
    }
    else if (!ft_strncmp(str, "cd", 2))
    {
        len = ft_strlen(getenv("HOME"));
        s = malloc(sizeof(char) * len);
        s = getenv("HOME");
		ft_env_pwd(getenv("PWD"), s, envp, 1);
        chdir(s);
    }
	if (!ft_strncmp(str, "exit", sizeof(str)))
    {
			printf("exit\n");
            exit (0);
    }
    if (!ft_strncmp(str, "env", sizeof(str)))
	{
		i = -1;
		while (envp[++i])
		{
			j = -1;
			while (envp[i][++j])
				printf ("%c", envp[i][j]);
			printf ("\n");
		}	
	}
	if (!ft_strncmp(str, "unset", 5))
	{
        char    *sub = ft_substr(str, 6, sizeof(str) - 5);
        printf("%s\n", sub);
        i = 0;
        while (envp[i])
        {
            if (!ft_strncmp(envp[i], sub, sizeof(sub)))
                printf("%s\n", envp[i]);
            i++;
        }
        printf("%s\n", envp[i - 2]);
    }
    if (!ft_strncmp(str, "export", 6))
    {
        if (ft_strchr(str, '='))
        {
            int lenght = 0;
            while (envp[lenght])
                lenght++;
            char    **env_var = malloc(sizeof(char *) * (lenght + 1));
            copy_env(env_var, envp);
            free(envp);
            i = 0;
		    while (env_var[i])
                i++;
            env_var[i] = env_var[i - 1];
            env_var[i - 1] = str + 7;
            printf("%s\n", env_var[i - 1]);
            env_var[i + 1] = 0;
        }
    }
}

void    copy_env(char **var_env, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        var_env[i] = envp[i];
        i++;
    }
}

int	main(int argc, char **argv, char **envp)
{	
    char    *str;
    char    **var_env;
    int     lenght;

	(void)argc;
    (void)argv;
    signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
    lenght = 0;
    while (envp[lenght])
        lenght++;
    while (1)
    {
        str = readline(BEGIN "My Term $ " CLOSE);
		if (!str)
		{
			printf ("exit\n");
			exit(0);
		}
		ft_env_(str, envp);
        if (str && *str)
            add_history(str);
		var_env = malloc(sizeof(char *) * lenght);
        copy_env(var_env, envp);
        check_pipe(str);
        do_cmd(str, var_env);
        free(str);
    }
}
