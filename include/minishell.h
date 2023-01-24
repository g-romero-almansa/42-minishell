/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:14:53 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/24 15:55:16 by barbizu-         ###   ########.fr       */
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

# define BEGIN "\001\033[m\002"
# define CLOSE "\001\033[0m\002"

/*MINISHELL*/
void	do_cmd(char *str, char **envp);

void    copy_env(char **var_env, char **envp);

/*FT_ENV*/
void	ft_env_pwd(char *old, char *nev, char **env, int num);

void	ft_update_env(char *var, char *pwd, char **env);

void	ft_env_(char *nev, char **env);

/*FT_UTILS*/
char	*ft_last_word(char *s);

/*PIPES*/
void	do_pipes(char *str);

void	check_pipe(char *str);

#endif
