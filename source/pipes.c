/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:45:49 by barbizu-          #+#    #+#             */
/*   Updated: 2023/02/23 10:46:18 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void    exec(char **pipe_sep, t_shell *p, int i)
{
    char    *path_env;
    char    **paths_sep;
    char    **str_sep;
    char    *cmd;

    str_sep = ft_split(pipe_sep[i], ' ');
    pipe_sep[i] = ft_strtrim(pipe_sep[i], " ");
    if (check_builtin(str_sep[0]))
        do_builtin(pipe_sep[i], p);
    else
    {
        path_env = find_path(p);
        if (!path_env)
        {
            ft_putstr_fd(str_sep[0], 2);
            ft_putendl_fd(": No such file or directory", 2);
            free_matrix(str_sep);
            free_matrix(pipe_sep);
            g_error = 127;
            exit(127);
        }
        paths_sep = ft_split(path_env, ':');
        cmd = paths_arg(paths_sep, str_sep);
        if (!cmd)
        {
            free_matrix(paths_sep);
            ft_putstr_fd(str_sep[0], 2);
            ft_putendl_fd(": command not found", 2);
            free_matrix(str_sep);
            free_matrix(pipe_sep);
            g_error = 127;
            exit(127);
        }
        execve(cmd, str_sep, p->var_env);
    }
}

void    ft_pipe(char **pipe_sep, int *prevpipe, int i, t_shell *p)
{
    int fd[2];

    if (pipe(fd) < 0)
    {
        g_error = errno;
        perror("Error: ");
        exit(errno);
    }
    p->child_pid[i] = fork();
    if (p->child_pid[i] == -1)
    {
        g_error = errno;
        perror("Error: ");
    }
    else if (p->child_pid[i] == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        p->fd_out = fd[1];
        close(fd[1]);
        dup2(*prevpipe, STDIN_FILENO);
        close(*prevpipe);
        exec(pipe_sep, p, i);
    }
    else
    {
        close(fd[1]);
        close(*prevpipe);
        *prevpipe = fd[0];
    }
}

void    ft_last(char **pipe_sep, int *prevpipe, int i, t_shell *p)
{
    int     j;
    int     status;

    p->child_pid[i] = fork();
    if (p->child_pid[i] == -1)
    {
        g_error = errno;
        perror("Error: ");
    }
    else if (p->child_pid[i] == 0)
    {
        dup2(*prevpipe, STDIN_FILENO);
        close(*prevpipe);
        exec(pipe_sep, p, i);
    }
    else
    {
        close(*prevpipe);
        j = 0;
        while (j <= p->n_pipes)
        {
            waitpid(p->child_pid[j], &status, 0);
            if (WIFEXITED(status))
                g_error = WEXITSTATUS(status);
            j++;
        }
    }
}

void    do_pipes(char *str, t_shell *p)
{
    int     prevpipe;
    int     i;
    char    **pipe_sep;

    prevpipe = dup(0);
    if (prevpipe == -1)
    {
        g_error = errno;
        perror("Error: ");
    }
    pipe_sep = ft_split(str, '|');
    p->n_pipes = 0;
    while (pipe_sep[p->n_pipes])
        p->n_pipes++;
    p->child_pid = (pid_t *)malloc(sizeof(pid_t) * (p->n_pipes + 1));
    if (!p->child_pid)
    {
        g_error = errno;
        perror("Error: ");
    }
    i = 0;
    while (i <= p->n_pipes)
    {
        if (pipe_sep[i] && pipe_sep[i + 1])
            ft_pipe(pipe_sep, &prevpipe, i, p);
        else if (pipe_sep[i + 1] == NULL)
            ft_last(pipe_sep, &prevpipe, i, p);
        i++;
    }
    free(p->child_pid);
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
