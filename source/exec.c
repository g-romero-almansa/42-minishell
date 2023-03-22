/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:42:00 by barbizu-          #+#    #+#             */
/*   Updated: 2023/03/07 12:42:03 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int check_exec(char *str)
{
    if (!ft_strncmp(str, "./", 2))
        return (1);
    return (0);
}

void    exec_file(char *str, char **argv)
{
    int     len;
    char    *pwd;
    char    *dir;
    pid_t   pid;
    int     status;

    pid = fork();
    status = 0;
    if (pid == 0)
    {
        len = ft_strlen(getenv("PWD"));
        pwd = malloc(sizeof(char) * (len + ft_strlen(str)));
        getcwd(pwd, len + 1);
        dir = malloc(sizeof(char) * (ft_strlen(str) - 2));
        dir = ft_strchr(str, '/');
        pwd = ft_strjoin(pwd, dir);
        if (execve(pwd, argv, var_env) == -1)
        {
            ft_putstr_fd(str, 2);
            printf(": %s\n", strerror(errno));
            exit(status);
        }
        //else
        //  SHLVL++
    }
    waitpid(pid, &status, 0);
}