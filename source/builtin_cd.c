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

void    do_cd_back(void)
{
    char    *s;

    chdir("..");
    s = malloc (sizeof(char) * ft_strlen(getenv("PWD")));
    getcwd(s, ft_strlen(getenv("PWD")));
    ft_env_pwd(getenv("PWD"), s, var_env, 1);
    rl_on_new_line();
}

void    do_cd_home(void)
{
    char    *s;
    int     len;

    len = ft_strlen(getenv("HOME"));
    s = malloc(sizeof(char) * len);
    s = getenv("HOME");
    ft_env_pwd(getenv("PWD"), s, var_env, 1);
    chdir(s);
}

void    do_cd(char *str)
{
    DIR     *dirp;
    char    *dir;
    char    *pwd;
    int     len;
    char    *path_dir;
    
    if (!ft_strncmp(str, "cd ..", sizeof(str)))
        do_cd_back();
    else if (!ft_strncmp(str, "cd ", sizeof(str)))
        do_cd_home();
    else
    {
        dir = malloc(sizeof(char) * (ft_strlen(str) - 3));
        dir = ft_strchr(str, ' ');
        dir[0] = '/';
        len = ft_strlen(getenv("PWD"));
        pwd = malloc(sizeof(char) * (len + 1));
        getcwd(pwd, len + 1);
        path_dir = ft_strjoin(pwd, dir);
        dirp = opendir(path_dir);
        if (dirp == NULL)
            printf("%s: %s\n", str, strerror(errno));
        else
        {
            ft_env_pwd(pwd, path_dir, var_env, 1);
            chdir(path_dir);
            closedir(dirp);
        }
    }
}
