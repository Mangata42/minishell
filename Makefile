# # CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft -g
# CGLAGS = -g -I includes -g3 -I libft

# LIBFT_TARGET = libft/libft.a

# SRC_DIR = src
# SRC_FILES = $(shell find src -name '*.c')
# OBJS = $(SRC_FILES:.c=.o)

# NAME = minishell

# VALGRIND = valgrind --suppressions=readline.supp --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all
# # VALGRIND = valgrind --suppressions=readline.supp


# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT_TARGET)
# 	gcc $(CFLAGS) $(OBJS) -L libft -l ft -l readline -o $(NAME)

# %.o: %.c
# 	gcc $(CFLAGS) -c $< -o $@

# $(LIBFT_TARGET):
# 	make -C libft

# clean:
# 	make clean -C libft
# 	rm -f $(OBJS)

# fclean: clean
# 	make fclean -C libft
# 	rm -f $(NAME)

# re: fclean all

# # Cible pour exécuter Valgrind avec suppression
# leak: all
# 	echo "{\nignore_libreadline_leaks\n Memcheck:Leak\n ...\n obj:/libreadline.so.\n }" > readline.supp
# 	$(VALGRIND) ./$(NAME)
# 	rm -f readline.supp

# .PHONY: all clean fclean re leak
# Variables
# Colors and formatting
# Colors and formatting
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
BLUE = \033[34m
BOLD = \033[1m
RESET = \033[0m
CLEAR = \033[2K\r

# Progress bar variables
TOTAL_FILES = $(shell find $(SRC_DIR) -name '*.c' | wc -l)
CURRENT_FILE = 0
BAR_WIDTH = 40

# Function to update progress bar
define progress_bar
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "$(CLEAR)$(BLUE)$(BOLD)Building minishell $(RESET)$(YELLOW)[$(RESET)"
	@progress=$$(echo "$(CURRENT_FILE) * $(BAR_WIDTH) / $(TOTAL_FILES)" | bc -l); \
	filled=$$(printf "%.0f" $$progress); \
	remaining=$$(echo "$(BAR_WIDTH) - $$filled" | bc); \
	for i in $$(seq 1 $$filled); do printf "█"; done; \
	for i in $$(seq 1 $$remaining); do printf "░"; done; \
	printf "$(YELLOW)]$(RESET) $(CURRENT_FILE)/$(TOTAL_FILES) files"
endef

# Variables
NAME = minishell
# CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft -g
CFLAGS = -Iincludes -Ilibft -g
LIBFT_TARGET = libft/libft.a
VALGRIND = valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

# Fichiers sources et objets
SRC_DIR = src
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRC_FILES:.c=.o)

# Règles de compilation
all: print_start $(LIBFT_TARGET) $(NAME)

print_start:
	@printf "$(BLUE)$(BOLD)► Starting minishell compilation...$(RESET)\n"

$(NAME): $(OBJS) $(LIBFT_TARGET)
	@printf "$(CLEAR)$(BLUE)$(BOLD)► Linking minishell...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -lreadline -o $(NAME)
	@printf "$(GREEN)$(BOLD)✓ Successfully built $(NAME)$(RESET)\n"

# Compilation des fichiers objets avec barre de progression
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call progress_bar)

# Compilation de libft avec animation simplifiée
$(LIBFT_TARGET):
	@printf "$(BLUE)$(BOLD)► Building libft...$(RESET)\n"
	@make -C libft > /dev/null
	@printf "$(GREEN)$(BOLD)✓ libft built successfully$(RESET)\n"

# Nettoyage des objets
clean:
	@printf "$(YELLOW)► Cleaning object files...$(RESET)\n"
	@make clean -C libft > /dev/null
	@rm -f $(OBJS)
	@printf "$(GREEN)✓ Clean complete$(RESET)\n"

# Nettoyage complet
fclean: clean
	@printf "$(YELLOW)► Removing executables...$(RESET)\n"
	@make fclean -C libft > /dev/null
	@rm -f $(NAME)
	@printf "$(GREEN)✓ Full clean complete$(RESET)\n"

# Rebuild complet
re: fclean all

# Cible pour exécuter Valgrind avec suppression
leak: all
	@printf "$(BLUE)$(BOLD)► Running Valgrind memory check...$(RESET)\n"
	@echo "{\nignore_libreadline_leaks\n Memcheck:Leak\n ...\n obj:/libreadline.so.\n }" > readline.supp
	@$(VALGRIND) ./$(NAME)
	@rm -f readline.supp

.PHONY: all clean fclean re leak print_start