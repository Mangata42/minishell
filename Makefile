# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 14:35:20 by nghaddar          #+#    #+#              #
#    Updated: 2024/10/29 17:45:57 by nghaddar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft -g
CGLAGS = -g -I includes -I libft

LIBFT_TARGET = libft/libft.a

SRC_DIR = src
SRC_FILES = $(shell find src -name '*.c')
# SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/lexer/builtins/*.c)
OBJS = $(SRC_FILES:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_TARGET)
	gcc $(CFLAGS) $(OBJS) -L libft -l ft -l readline -o $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(LIBFT_TARGET):
	make -C libft

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re