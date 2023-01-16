/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/16 13:51:35 by gromero-         ###   ########.fr       */
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

int	main(void)
{
	//struct sigaction	sig;

	//sig.sa_sigaction = sighandler;
	//sig.sa_flags = SA_SIGINFO;
	signal(SIGINT, sighandler);
	while (1)
    {
        char    *str = readline(BEGIN "My Shell $ " CLOSE);
        if (str && *str)
            add_history(str);
        if (!ft_strncmp(str, "pwd", sizeof(str)))
        {
            char    *pwd = malloc(sizeof(char) * 256);
            pwd = getcwd(pwd, sizeof(pwd));
            printf("%s\n", pwd);
            rl_on_new_line();
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
        free(str);
    }
}
