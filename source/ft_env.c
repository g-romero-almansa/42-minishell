/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:03:46 by gromero-          #+#    #+#             */
/*   Updated: 2023/05/09 12:24:40 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	**ft_cpy_env(char **env, char **cpy, int max)
{
	int	i;

	i = -1;
	while (++i < max && env[i])
		cpy[i] = ft_strdup(env[i]);
	cpy[i] = NULL;
	return (cpy);
}

void	ft_env_(char *nev, char **env, int max)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (ft_strncmp(nev, "echo $_", ft_strlen(nev)))
	{
		while (i < max)
		{
			if (!ft_strncmp(env[i], "_=", 2))
				break ;
			i++;
		}
		nev = ft_last_word(nev);
		k = -1;
		free (env[i]);
		env[i] = malloc ((ft_strlen(nev) + 3) * sizeof(char));
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
	char	*sub;

	i = 0;
	while (env[i] && ft_strncmp(env[i], var, ft_strlen(var)))
		i++;
	j = 0;
	while (env[i][j] != '=')
		j++;
	k = -1;
	sub = ft_substr(env[i], 0, j + 1);
	free(env[i]);
	env[i] = ft_strjoin(sub, pwd);
	free(sub);
}

void	ft_env_pwd(char *old, char *nev, char **env)
{
	ft_update_env("OLDPWD", old, env);
	ft_update_env("PWD", nev, env);
}
