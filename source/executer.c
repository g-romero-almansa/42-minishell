#include "../include/minishell.h"

void    executer(t_shell *p, char **argv)
{
    int i;
    int prevpipe;

    i = 0;
    prevpipe = dup(0);
    if (prevpipe == -1)
    {
        g_error = errno;
        perror("Error: ");
    }
    p->child_pid = (pid_t *)malloc(sizeof(pid_t) * (p->n_pipes + 1));
    if (!p->child_pid)
    {
        g_error = errno;
        perror("Error: ");
    }
    if (p->n_pipes == 0)
    {
        if (check_builtin(p->str))
            do_builtin(p->str, p);
        else if (check_exec(p->str))
            exec_file(argv, p);
        else
            find_cmd(p);
    }
    else
    {
        while (i <= p->n_pipes)
        {
            if (p->pipes[i] && p->pipes[i + 1])
                ft_pipe(p->pipes[i]->str, &prevpipe, i, p);
            else if (p->pipes[i + 1] == NULL)
                ft_last(p->pipes[i]->str, &prevpipe, i, p);
            i++;
        }
    }
}