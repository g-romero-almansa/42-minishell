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

void    add_level(char *str, t_t *p)
{
    int     i;
    char    *sub;
    int     num;

    i = 0;
    if (!ft_strncmp(str, "/minishell", sizeof(str)))
    {
        while (i <= p->env_n && var_env[i])
        {
            if (!ft_strncmp(var_env[i], "SHLVL=", 6))
            {
                sub = ft_strchr(var_env[i], '=');
                num = ft_atoi(sub + 1);
                num++;
                sub = ft_strjoin("SHLVL=", ft_itoa(num));
                var_env[i] = sub;
            }
            i++;
        }
    }
}

void    exec_file(char *str, char **argv, t_t *p)
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
        add_level(dir, p);
        if (execve(pwd, argv, var_env) == -1)
        {
            ft_putstr_fd(str, 2);
            ft_putendl_fd(strerror(errno), 2);
            exit(status);
        }
    }
    waitpid(pid, &status, 0);
}