/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/12 11:05:59 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

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
}

int	main(void)
{
	char    *str;

    while (1)
    {
        str = readline(BEGIN "My Shell $" CLOSE);
        if (str && *str)
            add_history(str);
        do_cmd(str);
        free(str);
    }
}