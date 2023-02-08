/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:14:53 by gromero-          #+#    #+#             */
/*   Updated: 2023/02/08 11:01:27 by gromero-         ###   ########.fr       */
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

# define BEGIN "\001\033[m\002"
# define CLOSE "\001\033[0m\002"

char    **var_env;

typedef struct s_t
{
	int		env_n;
}	t_t;

/*MINISHELL*/
void	do_cmd(char *str, t_t *p);
void    copy_env(char **new, char **envp);
int     check_builtin(char *str);

/*FT_ENV*/
void	ft_env_pwd(char *old, char *nev, char **env, int num);

void	ft_update_env(char *var, char *pwd, char **env);

void	ft_env_(char *nev, char **env);

char	**ft_cpy_env(char **envp, char **cpy, int max);

/*FT_EXPORT*/

char 	**ft_export(char *str, char **cpy, int i);

char	**ft_unset(char *str, char **cpy, int i);

/*FT_ECHO*/

int		ft_echo(char *s, char **envp, int i);

size_t	ft_count(char *s);

/*FT_UTILS*/
char	*ft_last_word(char *s);

void	ft_free_env(char **var_env, int j);

/*PIPES*/
void	do_pipes(char *str);

int     check_pipe(char *str);

/*COMMAND*/
char	*find_path(char **var_env);
char	*ft_paths_arg(char **paths_sep, char *str);
void	free_matrix(char **matrix);
void    find_cmd(char *str, char **var_env, char **argv);

#endif
