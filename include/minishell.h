#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BEGIN "\001\033[m\002"
#define CLOSE "\001\033[0m\002"

/*MINISHELL*/
char    *get_user(char *pwd);
void    do_cmd(char *str);

#endif