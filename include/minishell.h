/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:14:53 by gromero-          #+#    #+#             */
/*   Updated: 2023/05/11 11:13:55 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define BEGIN "\001\033[m\002"
# define CLOSE "\001\033[0m\002"

int					g_error;

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
}					t_token_type;

typedef struct s_pipes
{
	char			*str;
}					t_pipes;

typedef struct s_token
{
	t_token_type	token_type;
	char			*value;
}					t_token;

typedef struct s_shell
{
	int				env_n;
	int				flag_s;
	int				flag_d;
	int				flag_qu;
	char			**var_env;
	pid_t			*child_pid;
	int				n_pipes;
	int				n_tokens;
	int				interp;
	int				fd_out;
	int				fd_in;
	int				append;
	char			*str;
	t_token			**tokens;
	t_pipes			**pipes;
}					t_shell;

/*MINISHELL*/
void				sighandler(int num);
void				do_builtin(char *str, t_shell *p);
int					check_builtin(char *str);
void				free_executer(t_shell *p);

/*FT_INIT*/
void				init_p(char **envp, t_shell *p);
void				re_init(t_shell *p);
void				init(t_shell *p, char *str, char **argv);
void				control_d(void);

/*FT_ENV*/
void				ft_env_pwd(char *old, char *nev, char **env);
void				ft_update_env(char *var, char *pwd, char **env);
void				ft_env_(char *nev, char **env, int max);
char				**ft_cpy_env(char **env, char **cpy, int max);

/*FT_EXPORT*/
char				**ft_export(char *str, char **cpy, t_shell *p);
void				exp_remove(t_shell *p, char **cpy, char *sub, char *str);
void				exp_change(t_shell *p, char **cpy, char *str);
void				ft_show_export(t_shell *p);
void				export_order(t_shell *p, int j);
char				**ft_unset(char *str, char **cpy, t_shell *p);
int					unset_copy(int k, int less, t_shell *p, char **cpy);

/*FT_ECHO*/
void				search_echo(char *p, char **envp, int max);
int					ft_echo(char *s, char **envp, int i, int max);
size_t				ft_count(char *s);
void				echo_low_bar(char *str, char **envp, int max);

/*FT_UTILS*/
char				*ft_last_word(char *s);
void				ft_free_env(char **env, int j);

/*PIPES*/
void				do_pipes(t_shell *p);
int					check_pipe(char *str);
void				ft_last(char *str, int *prevpipe, int i, t_shell *p);
void				ft_pipe(char *str, int *prevpipe, int i, t_shell *p);

/*EXEC_PIPES*/
void				exec(char *str, t_shell *p);
void				exec_cmd(char **str_sep, t_shell *p);
void				child_pipe(t_shell *p, int *prevpipe, char *str, int *fd);
void				last_child(int *prevpipe, char *str, t_shell *p);

/*COMMAND*/
char				*find_path(t_shell *p);
char				*paths_arg(char **paths_sep, char **arg);
void				free_matrix(char **matrix);
void				c_proccess(t_shell *p);
void				find_cmd(t_shell *p);

/*BUILTIN*/
void				do_env(t_shell *p);
void				do_pwd(t_shell *p);
void				do_unset(t_shell *p, char *str);
void				export_cnt(t_shell *p, char *str);
void				do_export(char *str, t_shell *p);

/*BUILTIN_CD*/
char				*get_env(char *s, t_shell *p);
void				do_cd_back(t_shell *p);
void				do_cd_home(t_shell *p);
void				open_dir(char *path_dir, char *str, t_shell *p);
void				do_cd(char *str, t_shell *p);

/*BUILTIN_ECHO*/
int					echo_status(int i);
void				print_echo(char *str, t_shell *p);
void				do_echo(char *str, t_shell *p);

/*EXEC*/
int					check_exec(char *str);
void				add_level(char *dir, t_shell *p);
void				exec_child(t_shell *p, char **argv);
void				exec_file(char **argv, t_shell *p);

/*REDIRECT*/
int					check_redir(char *str);
void				do_redir(char *str, t_shell *p);

/*REDIR_IN*/
void				child_input(char *file, char *str, t_shell *p);
void				double_child_input(t_shell *p, char *delim);
void				input_redir(char *str, t_shell *p);
void				double_input(char *str, t_shell *p);

/*REDIR_OUT*/
void				out_child(char *file, char *str, t_shell *p);
void				output_redir(char *str, t_shell *p);
void				double_out_child(char *file, char *str, t_shell *p);
char				**sep_redir(char *str);
void				double_output(char *str, t_shell *p);

/*TOKENS*/
char				*token_quote(char *str, int *i);
char				*token_dredir(char *str, int *i, int start);
char				*token_pipe(char *str, int *i, int start);

/*LEXER*/
int					count_tokens(char *str);
void				lexer(char *str, t_shell *p);
char				*get_next_token(char *str, int *i);
t_token_type		get_token_type(char *token, t_token_type token_type);

/*PARSER*/
void				free_tokens(t_shell *p);
void				join_tokens(t_shell *p, int start, int end, int n);
void				init_parser(t_shell *p);
void				parser_quote(char *str, t_shell *p);
void				parser(t_shell *p);

/*EXECUTER*/
void				executer(t_shell *p, char *str, char **argv);

/*REDIR_PIPE*/
void				input_redir_pipe(char *str, t_shell *p);
void				output_redir_pipe(char *str, t_shell *p);
void				double_output_pipe(char *str, t_shell *p);
void				do_redir_pipe(char *str, t_shell *p);

/*EXIT*/
void				exit_num(t_shell *p, char *str);
void				do_exit(char *str, t_shell *p);
void				free_exit(t_shell *p, char *str);

/*ERROR*/
void				error_cmd(char *str);
void				std_error(void);
void				error_nofile(char *str);

#endif
