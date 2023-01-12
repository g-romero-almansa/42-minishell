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

int	main()
{
	while (1)
    {
        char    *str = readline(BEGIN "My Shell $" CLOSE);
        if (str && *str)
            add_history(str);
        if (!ft_strncmp(str, "pwd", sizeof(str)))
        {
            char    *pwd = malloc(sizeof(char) * 1000);
            getcwd(pwd, 1000);
            printf("%s\n", pwd);
            rl_on_new_line();
        }
		if (!ft_strncmp(str, "echo -n", 7))
        {
            printf("%s", str + 8);
			rl_on_new_line();
        }
		if (!ft_strncmp(str, "cd ", 3))
        {
            if (!ft_strncmp(str, "cd .", sizeof(str)))
				rl_on_new_line();
        }
        free(str);
    }
}
