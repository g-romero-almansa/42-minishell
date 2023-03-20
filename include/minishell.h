/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:14:53 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/20 11:21:32 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>

# define BEGIN "\001\033[m\002"
# define CLOSE "\001\033[0m\002"

char    **var_env;

typedef struct s_t
{
	int		env_n;
	int		flag_s;
	int		flag_d;
	int		flag_qu;
	int		e_status;
}	t_t;

/*MINISHELL*/
void	do_builtin(char *str, t_t *p);
int     check_builtin(char *str);

/*FT_ENV*/
void	ft_env_pwd(char *old, char *nev, char **env, int num);

void	ft_update_env(char *var, char *pwd, char **env);

void	ft_env_(char *nev, char **env, int max);

char	**ft_cpy_env(char **env, char **cpy, int max);

/*FT_EXPORT*/

char 	**ft_export(char *str, char **cpy, int i);

char	**ft_unset(char *str, char **cpy, int i);

/*FT_ECHO*/

int		ft_echo(char *s, char **envp, int i);

size_t	ft_count(char *s);

void	echo_low_bar(char *str, char **envp, int max);

int		ft_quotes(char *s, int i, char c, t_t *p);

/*FT_UTILS*/
char	*ft_last_word(char *s);

void	ft_free_env(char **env, int j);

/*PIPES*/
void	do_pipes(char *str, t_t *p);
int     check_pipe(char *str);
void    ft_last(char **pipe_sep, int *prevpipe, int i, t_t *p);
void    ft_pipe(char **pipe_sep, int *prevpipe, int i, t_t *p);
void    exec(char **pipe_sep, int i, t_t *p);

/*COMMAND*/
char	*find_path(char **var_env);
char	*paths_arg(char **paths_sep, char **arg);
void	free_matrix(char **matrix);
void	c_proccess(int status, char *str, char **str_sep, t_t *p);
void    find_cmd(char *str, t_t *p);

/*BUILTIN*/
int		echo_status(t_t *p, int i);
void    do_env(t_t *p);
void    do_pwd(void);
void    do_echo(char *str, t_t *p);
void    do_unset(t_t *p, char *str);
void    do_export(char *str, t_t *p);

/*BUILTIN_CD*/
void	do_cd_back(void);
void	do_cd_home(void);
void	do_cd(char *str);

/*EXEC*/
int		check_exec(char *str);
void	exec_file(char *str, char **argv);

#endif
