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

void    do_cd_back(t_shell *p)
{
    char    *s;

    chdir("..");
    s = malloc (sizeof(char) * ft_strlen(getenv("PWD")));
    if (!s)
    {
        g_error = errno;
        perror("Error: ");
    }
    getcwd(s, ft_strlen(getenv("PWD")));
    ft_env_pwd(getenv("PWD"), s, p->var_env, 1);
    rl_on_new_line();
}

void    do_cd_home(t_shell *p)
{
    char    *s;
    int     len;

    len = ft_strlen(getenv("HOME"));
    s = malloc(sizeof(char) * len);
    if (!s)
    {
        g_error = errno;
        perror("Error: ");
    }
    s = getenv("HOME");
    ft_env_pwd(getenv("PWD"), s, p->var_env, 1);
    chdir(s);
}

void    do_cd(char *str, t_shell *p)
{
    DIR     *dirp;
    char    *dir;
    char    *pwd;
    int     len;
    char    *path_dir;
    
    if (!ft_strncmp(str, "cd ..", sizeof(str)))
        do_cd_back(p);
    else if (!ft_strncmp(str, "cd ", sizeof(str)))
        do_cd_home(p);
    else
    {
        dir = malloc(sizeof(char) * (ft_strlen(str) - 3));
        if (!dir)
        {
            g_error = errno;
            perror("Error: ");
        }
        dir = ft_strchr(str, ' ');
        dir[0] = '/';
        len = ft_strlen(getenv("PWD"));
        pwd = malloc(sizeof(char) * (len + 1));
        if (!pwd)
        {
            g_error = errno;
            perror("Error: ");
        }
        getcwd(pwd, len + 1);
        path_dir = ft_strjoin(pwd, dir);
        dirp = opendir(path_dir);
        if (dirp == NULL)
        {
            g_error = 1;
            printf("%s: %s\n", str, strerror(errno));
        }
        else
        {
            ft_env_pwd(pwd, path_dir, p->var_env, 1);
            chdir(path_dir);
            closedir(dirp);
        }
        free(pwd);
        free(path_dir);
    }
}
