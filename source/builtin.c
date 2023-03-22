/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:53:02 by barbizu-          #+#    #+#             */
/*   Updated: 2023/03/13 11:37:27 by gromero-         ###   ########.fr       */
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

int echo_status(t_t *p, int i)
{
    (void)p;
    printf("%d", p->e_status);
    i++;
    rl_on_new_line();
    return (i);
}

void    do_echo(char *str, t_t *p)
{
    int i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
		if (str[i] == '>')
			flag++;
	if (flag == 1)
		ft_prueba(str, 1);
	else if (flag == 2)
		ft_prueba(str, 2);
	else if (!ft_strncmp(str, "echo -n", 7))
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
            else if (str[i] == '$' && str[i + 1] == '?')
                i = echo_status(p, i);
            else if (str[i] == '$')
				i = ft_echo(str, var_env, i) + i;
            else
				printf ("%c", str[i]);
        }
        printf("\n");
		rl_on_new_line();
    }
}

void    do_unset(t_t *p, char *str)
{
    char	**cpy;

    cpy = (char **)malloc((p->env_n + 1) * sizeof(char *));
    cpy = ft_cpy_env(var_env, cpy, p->env_n);
    ft_free_env(var_env, p->env_n);
    var_env = (char **)malloc((p->env_n) * sizeof(char *));
    var_env = ft_unset(str + 6, cpy, p->env_n);
    ft_free_env(cpy, p->env_n);
    p->env_n--;
}

void    do_export(char *str, t_t *p) //export sin variables
{
    char	**cpy;

    cpy = (char **)malloc((p->env_n + 1) * sizeof(char *));
    cpy = ft_cpy_env(var_env, cpy, p->env_n);
    ft_free_env(var_env, p->env_n);
    var_env = (char **)malloc((p->env_n + 2) * sizeof(char *));
    var_env = ft_export(str + 7, cpy, p->env_n);
    ft_free_env(cpy, p->env_n);
    p->env_n++;
}

void    do_env(t_t *p)
{
    int i;

    i = -1;
    while (++i <= p->env_n && var_env[i])
        printf ("%s\n", var_env[i]);
}
