# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 12:02:26 by gromero-          #+#    #+#              #
#    Updated: 2023/05/10 11:10:29 by gromero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC			=	source/minishell.c source/ft_env.c source/pipes.c \
				source/ft_utils.c source/ft_echo.c source/command.c \
				source/ft_export_unset.c source/builtin.c source/builtin_cd.c \
			   	source/redirect.c source/exec.c source/lexer.c source/parser.c \
				source/executer.c source/redir_pipe.c source/exit.c source/error.c \
				source/builtin_echo.c source/tokens.c source/redir_out.c \
				source/redir_in.c source/exec_pipes.c source/ft_init.c \
				source/export.c

OBJ_SRC		=	 $(SRC:.c=.o)

INC			=	./libft

LIB			=	libft.a

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra 
LFLAGS		=	-I /Users/$(USER)/.brew/opt/readline/include
FTFLAGS		=	-L /Users/$(USER)/.brew/opt/readline/lib
LREADLINE	=	-lreadline
HEADERS		=	-I ./include

all:	libft $(NAME)

libft:
	@$(MAKE) -C $(INC)

%.o: %.c
	$(CC)	$(CFLAGS)	$(LFLAGS)	-o	$@	-c	$<	$(HEADERS)

$(NAME) :	$(OBJ_SRC)
	$(CC)	$(OBJ_SRC)	$(FTFLAGS)	$(LFLAGS)	$(INC)/$(LIB)	$(HEADERS)	-o	$(NAME)	$(LREADLINE)

clean:
	rm -f $(OBJ_SRC)
	make -C $(INC) clean

fclean: clean
	rm -f $(NAME)
	make -C $(INC) fclean

re:	clean all

.PHONY: all clean fclean re libft
