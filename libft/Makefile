# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 15:30:39 by amoussai          #+#    #+#              #
#    Updated: 2019/10/26 17:13:47 by amoussai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a
SRCS =	ft_isalnum.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_calloc.c \
		ft_isascii.c \
		ft_bzero.c \
		ft_isdigit.c \
		ft_itoa.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_substr.c \
		ft_strlcpy.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strncat.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strncpy.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_isprint.c \
		ft_strcpy.c \
		ft_strcmp.c \
		ft_strcat.c \
		ft_strstr.c \
		ft_strtrim.c

OBJ =	$(SRCS:.c=.o)

BONUS_SRCS =	ft_lstadd_front_bonus.c \
				ft_lstnew_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstmap_bonus.c

BONUS_OBJ = $(BONUS_SRCS:.c=.o)

FLAGS=-Wall -Werror -Wextra
CC=gcc
INCLUDE=libft.h

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: all $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)

%.o : %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re: fclean all
