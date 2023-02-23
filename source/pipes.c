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

void    child_process(void)
{
    printf("h");
}
void    parent_process(void)
{
    printf("f");
}

void    do_pipes(char *str)
{
    int fd[2];
    int status;
    char    **pipe_sep;
    pid_t   child_pid;

    pipe_sep = ft_split(str, '|');
    if (pipe(fd) < 0)
        perror("Error en pipe");
    child_pid = fork();
    if (child_pid == -1)
        perror("Error en fork");
    else if (child_pid == 0)
        child_process();
    else
        parent_process();
    waitpid(-1, &status, 0);
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
