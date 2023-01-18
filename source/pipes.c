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
    pid_t   child_pid;

    (void)str;
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

void    check_pipe(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            do_pipes(str);
        i++;
    }
}