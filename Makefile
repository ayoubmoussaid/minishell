# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 15:30:39 by amoussai          #+#    #+#              #
#    Updated: 2021/02/03 12:54:39 by amoussai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
LIBFT=libft.a
SRCS=src/main.c src/builtins/*.c src/core/*.c src/parsing/variable_expansion.c src/execution/*.c src/utils/*.c


OBJ=$(SRCS:.c=.o)
GNL=./gnl/get_next_line.c ./gnl/get_next_line_utils.c
FLAGS=-Wall -Werror -Wextra
CC=gcc
CFLAGS=$(GNL) libft.a

.PHONY: clean bonus fclean all re

all: $(NAME)

$(NAME):
	@$(MAKE) -C ./libft
	@mv ./libft/$(LIBFT) .
	$(CC) $(FLAGS) $(SRCS) $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) -C ./libft clean
fclean: clean
	$(MAKE) -C ./libft fclean
	rm -f $(NAME)
	rm -f $(LIBFT)
re: fclean all
