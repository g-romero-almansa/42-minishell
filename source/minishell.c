/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/18 13:12:47 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	sighandler(int num)
{
	(void)num;
	printf ("\n");
	rl_redisplay();
	rl_on_new_line();
	rl_redisplay();
	rl_on_new_line();
	rl_redisplay();
}

void    do_cmd(char *str, char **envp)
{
    char    *pwd;
    char    *s;
    char    *dir;
    char    *path_dir;
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
        printf("%s\n", str + 5);
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
        chdir(s);
    }
	if (!ft_strncmp(str, "exit", sizeof(str)))
			exit (0);
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
	if (!ft_strncmp(str, "unset", sizeof(str)))
		unlink ("PRUEBA");
}

int	main(int argc, char **argv, char **envp)
{	
    char    *str;

	(void)argc;
    (void)argv;
    signal(SIGINT, sighandler);
    while (1)
    {
        str = readline(BEGIN "My Term $ " CLOSE);
        if (str && *str)
            add_history(str);
        check_pipe(str);
        do_cmd(str, envp);
        free(str);
    }
}
