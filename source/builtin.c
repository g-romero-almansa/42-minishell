/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:53:02 by barbizu-          #+#    #+#             */
/*   Updated: 2023/03/01 10:53:06 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void    do_pwd(void)
{
    int     len;
    char    *pwd;

    len = ft_strlen(getenv("PWD"));
    pwd = malloc(sizeof(char) * (len + 1));
    getcwd(pwd, len + 1);
    printf("%s\n", pwd);
    rl_on_new_line();
}

void    do_echo(char *str, t_t *p)
{
    int i;

    if (!ft_strncmp(str, "echo -n", 7))
	{
		printf("%s", str + 8);
		rl_on_new_line();
	}
    else if (!ft_strncmp(str, "echo", 4))
    {
        i = 4;
		while (str[++i])
        {
            if (str[i] == '$' && str[i + 1] == '_')
            {
                echo_low_bar(str, var_env, p->env_n);
                i++;
            }
            else if (str[i] == '$')
				i = ft_echo(str, var_env, i) + i;
            else
				printf ("%c", str[i]);
        }
        printf("\n");
		rl_on_new_line();
    }
}

void    do_unset(t_t *p, char *str) //no funciona para las variables de env
{
    char	**cpy;
    int     i;

    cpy = (char **)malloc((p->env_n) * sizeof(char *));
    cpy = ft_cpy_env(var_env, cpy, p->env_n);
    ft_free_env (var_env, p->env_n);
    var_env = (char **)malloc((p->env_n - 1) * sizeof(char *));
    var_env = ft_unset(str + 6, cpy, p->env_n);
    ft_free_env(cpy, p->env_n);
    i = -1;
    while (++i < p->env_n)
        printf ("%s\n", var_env[i]);
    p->env_n--;
}

void    do_export(char *str, t_t *p)
{
    char	**cpy;

    cpy = (char **)malloc((p->env_n + 1) * sizeof(char *));
    cpy = ft_cpy_env(var_env, cpy, p->env_n);
    ft_free_env (var_env, p->env_n);
    var_env = (char **)malloc((p->env_n + 1) * sizeof(char *));
    var_env = ft_export(str + 7, cpy, p->env_n);
    ft_free_env (cpy, p->env_n);
    p->env_n++;
}

void    do_env(t_t *p)
{
    int i;

    i = -1;
    while (++i <= (p->env_n))
        printf ("%s\n", var_env[i]);
}
