/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:03:46 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/02 11:13:08 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	**ft_cpy_env(char **envp, char **cpy, int max)
{
	int		i;

	i = -1;
	while (++i <= max)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
}

void	ft_env_(char *nev, char **env, int max)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	if (ft_strncmp(nev, "echo $_", ft_strlen(nev)))
	{
		while (i < max && ft_strncmp(env[i], "_=", 2))
			i++;
		nev = ft_last_word(nev);
		k = -1;
		env[i][0] = '_';
		env[i][1] = '=';
		j = 1;
		while (nev[++k])
			env[i][++j] = nev[k];
		env[i][j + 1] = '\0';
	}
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
