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

void    do_cmd(char *str)
{
    char    *pwd;
    char    *s;
    char    *dir;
    char    *path_dir;

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
        if (!ft_strncmp(str, "cd .", sizeof(str)))
            rl_on_new_line();
        else if (!ft_strncmp(str, "cd ..", sizeof(str)))
        {
            chdir("..");
            rl_on_new_line();
        }
        else if (!ft_strncmp(str, "cd ", sizeof(str)))
        {
            pwd = malloc(sizeof(char) * 1000);
            getcwd(pwd, 1000);
            s = malloc(sizeof(char) * 1000);
            s = get_user(pwd);
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
                chdir(path_dir);
            }
            else
            {
                dir = ft_strchr(str, '/');
                chdir(dir);
            }
        }
    }
	if (!ft_strncmp(str, "exit", sizeof(str)))
			exit (0);
	if (!ft_strncmp(str, "env", sizeof(str)))
	{
		printf ("TERM_SESSION_ID=%s\n", getenv("TERM_SESSION_ID"));
		printf ("PWD=%s\n", getenv("PWD"));
		printf ("HOME=%s\n", getenv("HOME"));
	}
	if (!ft_strncmp(str, "unset", sizeof(str)))
		unlink ("PRUEBA");
	//if (!ft_strncmp(str, "export", sizeof(str)))
	//sigaction(SIGINT, &sig, (void *)str);
}
int	main(void)
{
	char    *str;

	signal(SIGINT, sighandler);
    while (1)
    {
        str = readline(BEGIN "My Shell $" CLOSE);
        if (str && *str)
            add_history(str);
        do_cmd(str);
        free(str);
    }
}
