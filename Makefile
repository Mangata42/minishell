CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft -g
# CGLAGS = -g -I includes -g3 -I libft

LIBFT_TARGET = libft/libft.a

SRC_DIR = src
SRC_FILES = $(shell find src -name '*.c')
OBJS = $(SRC_FILES:.c=.o)

NAME = minishell

VALGRIND = valgrind --suppressions=readline.supp --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all
# VALGRIND = valgrind --suppressions=readline.supp


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

# Cible pour exécuter Valgrind avec suppression
leak: all
	echo "{\nignore_libreadline_leaks\n Memcheck:Leak\n ...\n obj:/libreadline.so.\n }" > readline.supp
	$(VALGRIND) ./$(NAME)
	rm -f readline.supp

.PHONY: all clean fclean re leak
