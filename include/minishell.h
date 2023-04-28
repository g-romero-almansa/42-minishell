/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:14:53 by gromero-          #+#    #+#             */
/*   Updated: 2023/04/27 12:27:31 by gromero-         ###   ########.fr       */
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
# include <sys/wait.h>

# define BEGIN "\001\033[m\002"
# define CLOSE "\001\033[0m\002"

int		g_error;

typedef enum e_token_type
{
	PIPE,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
	OUTFILE,
	INFILE,
	CMD,
	ARG
}				t_token_type;

typedef struct s_pipes
{
	char	*str;
	char	*input;
	char	*output;
}				t_pipes;

typedef struct s_token
{
	t_token_type	token_type;
	char			*value;
}				t_token;

typedef struct s_shell
{
	int		env_n;
	int		flag_s;
	int		flag_d;
	int		flag_qu;
	char	**var_env;
	pid_t	*child_pid;
	int		n_pipes;
	int		n_tokens;
	int		interp;
	int		fd_out;
	int		fd_in;
	char	*infile;
	char	*outfile;
	int		append;
	char	*str;
	t_token	**tokens;
	t_pipes	**pipes;
}				t_shell;

/*MINISHELL*/
void			do_builtin(char *str, t_shell *p);
int				check_builtin(char *str);

/*FT_ENV*/
void			ft_env_pwd(char *old, char *nev, char **env);
void			ft_update_env(char *var, char *pwd, char **env);
void			ft_env_(char *nev, char **env, int max);
char			**ft_cpy_env(char **env, char **cpy, int max);

/*FT_EXPORT*/
char			**ft_export(char *str, char **cpy, t_shell *p);
void			ft_show_export(t_shell *p);
char			**ft_unset(char *str, char **cpy, t_shell *p);

/*FT_ECHO*/
int				ft_echo(char *s, char **envp, int i);
size_t			ft_count(char *s);
void			echo_low_bar(char *str, char **envp, int max);
int				ft_quotes(char *s, int i, char c, t_shell *p);

/*FT_UTILS*/
char			*ft_last_word(char *s);
void			ft_free_env(char **env, int j);

/*PIPES*/
void			do_pipes(char *str, t_shell *p);
int				check_pipe(char *str);
void			ft_last(char *str, int *prevpipe, int i, t_shell *p);
void			ft_pipe(char *str, int *prevpipe, int i, t_shell *p);
void			exec(char *str, t_shell *p);

/*COMMAND*/
char			*find_path(t_shell *p);
char			*paths_arg(char **paths_sep, char **arg);
void			free_matrix(char **matrix);
void			c_proccess(t_shell *p);
void			find_cmd(t_shell *p);

/*BUILTIN*/
int				echo_status(int i);
void			do_env(t_shell *p);
void			do_pwd(t_shell *p);
void			do_echo(char *str, t_shell *p);
void			do_unset(t_shell *p, char *str);
void			do_export(char *str, t_shell *p);
void			do_exit(char *str);

/*BUILTIN_CD*/
char			*get_env(char *s, t_shell *p);
void			do_cd_back(t_shell *p);
void			do_cd_home(t_shell *p);
void			do_cd(char *str, t_shell *p);

/*EXEC*/
int				check_exec(char *str);
void			ft_prueba(char *s, int flag);
void			add_level(char *dir, t_shell *p);
void			exec_file(char **argv, t_shell *p);

/*REDIRECT*/
int				check_redir(char *str);
void			do_redir(char *str, t_shell *p);
void			output_redir(char *str, t_shell *p);
void			input_redir(char *str, t_shell *p);
void			double_output(char *str, t_shell *p);
void			double_input(char *str, t_shell *p);

/*LEXER*/
void			lexer(char *str, t_shell *p);
char			*get_next_token(char *str, int *i);
t_token_type	get_token_type(char *token, t_token_type token_type);

/*PARSER*/
void			parser(t_shell *p);

/*EXECUTER*/
void			executer(t_shell *p, char *str, char **argv);

/*REDIR_PIPE*/
void			input_redir_pipe(char *str, t_shell *p);
void			output_redir_pipe(char *str, t_shell *p);
void			double_output_pipe(char *str, t_shell *p);
void			do_redir_pipe(char *str, t_shell *p);

#endif
