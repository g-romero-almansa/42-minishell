/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/18 12:20:20 by gromero-         ###   ########.fr       */
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

char    *get_user(char *pwd)
{
    char    *s;
    int     i;
    int     n;

    i = 0;
    n = 0;
    while (n++ != 2)
    {
        i++;
        while (pwd[i] != '/')
            i++;
    }
    s = malloc(i * sizeof(char));
    ft_strlcpy(s, pwd, i + 1);
    return(s);
}

void    do_cmd(char *str, char **envp)
{
    char    *pwd;
    char    *s;
    char    *dir;
    char    *path_dir;
	int		i;
	int		j;

    if (!ft_strncmp(str, "pwd", sizeof(str)))
    {
        pwd = malloc(sizeof(char) * 1000);
        getcwd(pwd, 1000);
        printf("%s\n", pwd);
        rl_on_new_line();
    }
    else if (!ft_strncmp(str, "echo -n", 7))
    {
        printf("%s", str + 8);
        rl_on_new_line();
    }
    else if (!ft_strncmp(str, "cd ", 3))
    { 
        if (!ft_strncmp(str, "cd ..", sizeof(str)))
        {
			pwd = malloc(sizeof(char) * 1000);
			getcwd(pwd, 1000);
            chdir("..");
			s = malloc (sizeof(char) * 1000);
			getcwd(s, 1000);
			ft_env_pwd(pwd, s, envp, 1);
            rl_on_new_line();
        }
        else if (!ft_strncmp(str, "cd ", sizeof(str)))
        {
            pwd = malloc(sizeof(char) * 1000);
            getcwd(pwd, 1000);	
            s = malloc(sizeof(char) * 1000);
            s = get_user(pwd);
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
                pwd = malloc(sizeof(char) * 1000);
                path_dir = ft_strjoin(getcwd(pwd, 1000), dir);
				ft_env_pwd(pwd, path_dir, envp, 1);
                chdir(path_dir);
            }
            else
            {
				pwd = malloc(sizeof(char) * 1000);
				getcwd(pwd, 1000);
                dir = ft_strchr(str, '/');
				ft_env_pwd(pwd, dir, envp, 1);
                chdir(dir);
            }
        }
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
        do_cmd(str, envp);
        free(str);
    }
}
