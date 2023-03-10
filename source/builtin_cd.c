/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:35:45 by barbizu-          #+#    #+#             */
/*   Updated: 2023/03/06 12:35:49 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void    cd_back_home(int flag)
{
    char    *s;
    int     len;

    if (flag == 1)
    {
        chdir("..");
        s = malloc (sizeof(char) * ft_strlen(getenv("PWD")));
        getcwd(s, ft_strlen(getenv("PWD")));
        ft_env_pwd(getenv("PWD"), s, var_env, 1);
        rl_on_new_line();
    }
    else
    {
        len = ft_strlen(getenv("HOME"));
        s = malloc(sizeof(char) * len);
        s = getenv("HOME");
        ft_env_pwd(getenv("PWD"), s, var_env, 1);
        chdir(s);
    }
}

void    do_cd(char *str)
{
    char    *dir;
    char    *pwd;
    int     len;
    char    *path_dir;
    
    if (!ft_strncmp(str, "cd ..", sizeof(str)))
        cd_back_home(1);
    else if (!ft_strncmp(str, "cd ", sizeof(str)))
        cd_back_home(2);
    else
    {
        dir = malloc(sizeof(char) * (ft_strlen(str) - 3));
        dir = ft_strchr(str, ' ');
        dir[0] = '/';
        len = ft_strlen(getenv("PWD"));
        pwd = malloc(sizeof(char) * (len + 1));
        getcwd(pwd, len + 1);
        path_dir = ft_strjoin(pwd, dir);
        ft_env_pwd(pwd, path_dir, var_env, 1);
        chdir(path_dir);
    }
}
