# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 10:57:13 by gromero-          #+#    #+#              #
#    Updated: 2023/01/26 12:21:18 by gromero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	source/minishell.c source/ft_env.c source/pipes.c \
				source/ft_utils.c source/ft_echo.c source/command.c

OBJ_SRC		=	 $(SRC:.c = .o)

INC			=	./libft

LIB			=	libft.a

EXEC		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -lreadline -I /Users/$(USER)/.brew/opt/readline/include
FTFLGS		=	-Llibft -lft -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

all:		$(EXEC)

$(NAME):	all

$(LIB):
	make -C $(INC)

$(EXEC):	$(LIB)	$(OBJ_SRC)
	$(CC)	$(CFLAGS)	$(FTFLGS)	$(OBJ_SRC)	-o	$(EXEC)	$(INC)/$(LIB)

clean:
	rm -f $(EXEC)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re:	fclean all

.PHONY: all clean fclean re
