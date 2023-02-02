/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:05:28 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/31 13:01:11 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	sighandler(int num)
{
	if (num == SIGINT)
	{	
		rl_on_new_line();
		printf ("\n");
		rl_redisplay();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	do_cmd(char *str)
{
    char	*pwd;
    char	*s;
    char	*dir;
    char	*path_dir;
	int		i;
	int		j;
	int		len;

    len = 0;
    if (!ft_strncmp(str, "pwd", 3))
    {
		len = ft_strlen(getenv("PWD"));
		pwd = malloc(sizeof(char) * (len + 1));
		getcwd(pwd, len + 1);
		printf("%s\n", pwd);
		rl_on_new_line();
	}
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
            if (str[i] == '$')
				i = ft_echo(str, var_env, i) + i;
            else
				printf ("%c", str[i]);
        }
        printf("\n");
		rl_on_new_line();
	}
	else if (!ft_strncmp(str, "cd .", sizeof(str)))
        rl_on_new_line();
    else if (!ft_strncmp(str, "cd ", 3))
    { 
        if (!ft_strncmp(str, "cd ..", sizeof(str)))
        {
			pwd = malloc(sizeof(char) * ft_strlen(getenv("PWD")));
			getcwd(pwd, ft_strlen(getenv("PWD")));
            chdir("..");
			s = malloc (sizeof(char) * ft_strlen(getenv("PWD")));
			getcwd(s, ft_strlen(getenv("PWD")));
			ft_env_pwd(pwd, s, var_env, 1);
            rl_on_new_line();
        }
        else if (!ft_strncmp(str, "cd ", sizeof(str)))
        {
            pwd = malloc(sizeof(char) * ft_strlen(getenv("PWD")));
            getcwd(pwd, ft_strlen(getenv("PWD")));	
 			len = ft_strlen(getenv("HOME"));
            s = malloc(sizeof(char) * len);
            s = getenv("HOME");
			ft_env_pwd(pwd, s, var_env, 1);
            chdir(s);
        }
        else
        {
            dir = malloc(sizeof(char) * (ft_strlen(str) - 3));
            dir = ft_strchr(str, ' ');
            if (dir[1] != '/')
            {
                dir[0] = '/';
                len = ft_strlen(getenv("PWD"));
                pwd = malloc(sizeof(char) * (len + 1));
                getcwd(pwd, len + 1);
                path_dir = ft_strjoin(pwd, dir);
				ft_env_pwd(pwd, path_dir, var_env, 1);
				chdir(path_dir);
            }
            else
            {
				pwd = malloc(sizeof(char) * ft_strlen(getenv("PWD")));
				getcwd(pwd, ft_strlen(getenv("PWD")));
                dir = ft_strchr(str, '/');
				ft_env_pwd(pwd, dir, var_env, 1);
                chdir(dir);
            }
        }
    }
    else if (!ft_strncmp(str, "cd", 2))
    {
        len = ft_strlen(getenv("HOME"));
        s = malloc(sizeof(char) * len);
        s = getenv("HOME");
		ft_env_pwd(getenv("PWD"), s, var_env, 1);
        chdir(s);
    }
	if (!ft_strncmp(str, "exit", sizeof(str)))
    {
			printf("exit\n");
            exit (0);
    }
    if (!ft_strncmp(str, "env", sizeof(str)))
	{
		i = -1;
		while (var_env[++i])
		{
			j = -1;
			while (var_env[i][++j])
				printf ("%c", var_env[i][j]);
			printf ("\n");
		}	
	}
	if (!ft_strncmp(str, "unset", 5))
	{
        char    *sub;
        char    **var;
        int     del;
        
        sub = ft_substr(str, 6, sizeof(str) - 5);
        i = 0;
        while (var_env[i])
        {
            if (!ft_strncmp(var_env[i], sub, sizeof(sub)))
                del = i;
            i++;
        }
        var = malloc(sizeof(char *) * i);
        i = 0;
        while (var_env[i])
        {
            if (i == del)
                i++;
            else
                var[i] = var_env[i];
            i++;
        }
        free(var_env);
        var_env = var;
    }
    if (!ft_strncmp(str, "export", 6))
    {
		int		i;
		char	**env;
		i = 0;
		while (var_env[i])
			i++;
		env = (char **)malloc((i + 1) * sizeof(char *));
		if (!env)
			exit(0);
		env = ft_export(var_env, str, i, env);	
		var_env = (char **)malloc((i + 1) *sizeof(char *));
		if (!var_env)
			exit(0);
		ft_cpy_env(env, var_env);
        /*if (ft_strchr(str, '='))
        {
            char    **temp;
            int     lenght;

            lenght = 0;
            while (var_env[lenght])
                lenght++;
            temp = malloc(sizeof(char *) * (lenght + 1));
            ft_cpy_env(temp, var_env);
            temp[lenght] = temp[lenght - 1];
            temp[lenght - 1] = str + 7;
            temp[lenght + 1] = 0;
            var_env = malloc(sizeof(char *) * (lenght + 1));
            ft_cpy_env(var_env, temp);
            free(temp);
        }*/
    }
}

int check_builtin(char *str)
{
    if (!ft_strncmp(str, "pwd", 3))
        return (1);
    else if (!ft_strncmp(str, "cd", 2))
        return (1);
    else if (!ft_strncmp(str, "echo", 4))
        return (1);
    else if (!ft_strncmp(str, "exit", 4))
        return (1);
    else if (!ft_strncmp(str, "env", 3))
        return (1);
    else if (!ft_strncmp(str, "export", 6))
        return (1);
    else if (!ft_strncmp(str, "unset", 5))
        return (1);
    return (0);
}

int	main(int argc, char **argv, char **envp)
{	
    char    *str;
	int		i;

	(void)argc;
    (void)argv;
    signal(SIGINT, sighandler);
	i = 0;
	while (envp[i])
		i++;
	var_env = (char **)malloc(i * sizeof(char *));
	if (!var_env)
		exit(0);
    ft_cpy_env(envp, var_env);
    while (1)
    {
        str = readline(BEGIN "My Term $ " CLOSE);
		if (!str)
		{
            printf ("exit\n");
			exit(0);
		}
		ft_env_(str, var_env);
        if (str && *str)
            add_history(str);
        if (check_pipe(str))
            do_pipes(str);
        else if (check_builtin(str))
            do_cmd(str);
        else
            find_cmd(str, var_env, argv);
        free(str);
    }
}