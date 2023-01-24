/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:03:46 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/23 13:19:04 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_env_(char *nev, char **env)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "_=", 2))
		i++;
	nev = ft_last_word(nev);
	k = -1;
	ft_bzero(env[i], ft_strlen(env[i]));
	env[i][0] = '_';
	env[i][1] = '=';
	j = 1;
	while (nev[++k])
		env[i][++j] = nev[k];
	env[i][j + 1] = '\0';
}

void	ft_update_env(char *var, char *pwd, char **env)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (env[i] && ft_strncmp(env[i], var, ft_strlen(var)))
		i++;
	j = 0;
	while (env[i][j] != '=')
		j++;
	k = -1;
	while (pwd[++k])
		env[i][++j] = pwd[k];
	env[i][j + 1] = '\0';
}

void	ft_env_pwd(char *old, char *nev, char **env, int num)
{
	(void)num;
	ft_update_env("OLDPWD", old, env);
	ft_update_env("PWD", nev, env);
}