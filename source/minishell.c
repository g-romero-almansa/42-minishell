/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/16 13:59:08 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

/*void	sighandler(int signum, siginfo_t *inf, void *s)
{
	(void)inf;
	(void)signum;
	printf ("%s\n", (char *)s);
}*/
void	sighandler(int num)
{
	(void)num;
	printf ("\n");
	rl_on_new_line();
}

void    do_cmd(char *str, char **envp)
{
    int     len;
    int     i;
    int     j;
    char    *pwd;
    char    *s;
    char    *dir;
    char    *path_dir;

    len = 0;
    if (!ft_strncmp(str, "pwd", sizeof(str)))
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
    else if (!ft_strncmp(str, "cd ", 3))
    {
        if (!ft_strncmp(str, "cd .", sizeof(str)))
            rl_on_new_line();
        else if (!ft_strncmp(str, "cd ..", sizeof(str)))
        {
            chdir("..");
            rl_on_new_line();
        }
        else if (!ft_strncmp(str, "cd ", sizeof(str)))
        {
            len = ft_strlen(getenv("HOME"));
            s = malloc(sizeof(char) * len);
            s = getenv("HOME");
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
                pwd = malloc(sizeof(char) * (len + ft_strlen(str) - 3));
                path_dir = ft_strjoin(getcwd(pwd, len), dir);
                chdir(path_dir);
            }
            else
            {
                dir = ft_strchr(str, '/');
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
        i = 0;
        while (envp[i])
        {
            j = 0;
            while (envp[i][j])
            {
                printf("%c", envp[i][j]);
                j++;
            }
            printf("\n");
            i++;
        }
	}
	if (!ft_strncmp(str, "unset", sizeof(str)))
		unlink ("PRUEBA");
	//if (!ft_strncmp(str, "export", sizeof(str)))
	//sigaction(SIGINT, &sig, (void *)str);
}

int	main(int argc, char **argv, char **envp)
{	
    char    *str;

	(void)argc;
    (void)argv;
    signal(SIGINT, sighandler);
    while (1)
    {
        str = readline(BEGIN "My Shell $" CLOSE);
        if (str && *str)
            add_history(str);
        check_pipe(str);
        do_cmd(str, envp);
        free(str);
    }
}
