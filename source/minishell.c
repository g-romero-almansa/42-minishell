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
            char    *pwd = malloc(sizeof(char) * 256);
            pwd = getcwd(pwd, sizeof(pwd));
            printf("%s\n", pwd);
            rl_on_new_line();
        }
        free(str);
    }
}
