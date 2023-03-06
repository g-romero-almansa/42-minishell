/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:45:49 by barbizu-          #+#    #+#             */
/*   Updated: 2023/01/18 12:45:53 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void    exec(char **pipe_sep, int i)
{
    char    *path_env;
    char    **paths_sep;
    char    **str_sep;
    char    *cmd;

    path_env = find_path(var_env);
    paths_sep = ft_split(path_env, ':');
    str_sep = ft_split(pipe_sep[i], ' ');
    cmd = paths_arg(paths_sep, str_sep);
    if (!cmd)
    {
        free_matrix(paths_sep);
		free(cmd);
		ft_putstr_fd(str_sep[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(0);
    }
    execve(cmd, str_sep, var_env);
}

void    ft_pipe(char **pipe_sep, int *prevpipe, int i)
{
    int fd[2];
    pid_t   child_pid;

    if (pipe(fd) < 0)
        perror("Error en pipe");
    child_pid = fork();
    if (child_pid == -1)
        perror("Error en fork");
    else if (child_pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        dup2(*prevpipe, STDIN_FILENO);
        close(*prevpipe);
        exec(pipe_sep, i);
    }
    else
    {
        close(fd[1]);
        close(*prevpipe);
        *prevpipe = fd[0];
    }
}

void    ft_last(char **pipe_sep, int *prevpipe, int i)
{
    pid_t   last_pid;
    pid_t   check;

    last_pid = fork();
    if (last_pid == -1)
        perror("Error en fork");
    else if (last_pid == 0)
    {
        dup2(*prevpipe, STDIN_FILENO);
        close(*prevpipe);
        exec(pipe_sep, i);
    }
    else
    {
        close(*prevpipe);
        check = wait(0);
        while (check != -1)
            check = wait(0);
    }
}

void    do_pipes(char *str)
{
    int     prevpipe;
    int     n_pipes;
    int     i;
    char    **pipe_sep;

    prevpipe = dup(0);
    pipe_sep = ft_split(str, '|');
    n_pipes = 0;
    while (pipe_sep[n_pipes])
        n_pipes++;
    i = 0;
    while (i <= n_pipes)
    {
        if (pipe_sep[i] && pipe_sep[i + 1])
            ft_pipe(pipe_sep, &prevpipe, i);
        else if (pipe_sep[i + 1] == NULL)
            ft_last(pipe_sep, &prevpipe, i);
        i++;
    }
}

int check_pipe(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            return (1);
        i++;
    }
    return (0);
}
