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

void    add_level(char *dir, t_shell *p)
{
    int     i;
    char    *sub;
    int     num;

    i = 0;
    if (!ft_strncmp(dir, "/minishell", ft_strlen(dir)))
    {
        while (i < p->env_n && p->var_env[i])
        {
            if (!ft_strncmp(p->var_env[i], "SHLVL=", 6))
            {
                sub = ft_strchr(p->var_env[i], '=');
                num = ft_atoi(sub + 1);
                num++;
                sub = ft_strjoin("SHLVL=", ft_itoa(num));
                p->var_env[i] = sub;
                free(sub);
            }
            i++;
        }
    }
}

void    exec_file(char **argv, t_shell *p)
{
    int     len;
    char    *pwd;
    char    *dir;
    pid_t   pid;
    int     status;

    status = 0;
    pid = fork();
    if (pid == -1)
    {
        g_error = errno;
        perror("Error: ");
    }
    else if (pid == 0)
    {
        len = ft_strlen(get_env("PWD", p));
        pwd = malloc(sizeof(char) * (len + ft_strlen(p->str)));
        if (!pwd)
        {
            g_error = errno;
		    perror("Error: ");
		    exit(errno);
        }
        getcwd(pwd, len + 1);
        dir = malloc(sizeof(char) * (ft_strlen(p->str) - 2));
        if (!dir)
        {
            g_error = errno;
		    perror("Error: ");
		    exit(errno);
        }
        dir = ft_strchr(p->str, '/');
        pwd = ft_strjoin(pwd, dir);
        add_level(dir, p);
        if (execve(pwd, argv, p->var_env) == -1)
        {
            free(pwd);
            free(dir);
            ft_putstr_fd(p->str, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(errno), 2);
            g_error = 126;
            exit(126);
        }
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        g_error = WEXITSTATUS(status);
}