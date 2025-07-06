NAME	:= minishell

#################################
#			Config				#
#################################

CC	:= gcc

#################################
#			Flags				#
#################################

DEBUG_FLAGS	:= -g -fsanitize=address -fsanitize=undefined -O0
CFLAGS		:= -Wall -Wextra -Werror -D_GNU_SOURCE

#################################
#			Files				#
#################################

SRC = \
src/main.c \
src/utils/init.c \
src/utils/utils.c \
src/utils/pipes.c \
src/utils/utils1.c \
src/utils/utils2.c \
src/utils/utils3.c \
src/utils/prompt.c \
src/utils/get_path.c \
src/utils/here_doc.c \
src/execute/execute.c \
src/utils/free_vars.c \
src/utils/user_input.c \
src/utils/wait_childs.c \
src/utils/compare_fds.c \
src/ast_tree/ast_build.c \
src/utils/tokenization.c \
src/utils/env_to_array.c \
src/ast_tree/ast_utils.c \
src/ast_tree/ast_nodes.c \
src/expansion/expansion.c \
src/signals/sig_actions.c \
src/execute/execute_pipe.c \
src/builtins/ft_cd/ft_cd.c \
src/execute/execute_tree.c \
src/builtins/ft_pwd/ft_pwd.c \
src/builtins/ft_env/ft_env.c \
src/builtins/ft_echo/ft_echo.c \
src/execute/execute_redirect.c \
src/signals/sig_actions_quit.c \
src/builtins/ft_exit/ft_exit.c \
src/builtins/ft_unset/ft_unset.c \
src/expansion/expansion_quotes.c \
src/builtins/ft_cd/ft_cd_utils.c \
src/expansion/expansion_get_var.c \
src/expansion/expansion_heredoc.c \
src/builtins/ft_export/ft_export.c \
src/builtins/ft_env/ft_env_utils.c \
src/signals/sig_actions_here_doc.c \
src/builtins/ft_export/ft_export_utils.c \
src/builtins/ft_export/ft_export_utils1.c \
get_next_line/src/get_next_line.c \
get_next_line/src/get_next_line_utils.c \

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADERS = inc/minishell.h

OBJ_DIR = objects
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

#################################
#			Rules				#
#################################

all: $(NAME)
	@echo "\033[0;32m🎉 $(NAME) built successfully!\033[0m"

$(NAME): $(LIBFT) $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) -I inc -I libft/inc -I get_next_line/inc -o $(NAME) $(OBJ) $(LIBFT) -L/opt/homebrew/Caskroom/miniconda/base/lib -lreadline -lncurses

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I inc -I libft/inc -I get_next_line/inc -c $< -o $@

$(OBJ_DIR): $(HEADERS)
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@if [ ! -f $(LIBFT_DIR)/Makefile ]; then \
		echo "\033[0;33mInitializing submodules...\033[0m"; \
		git submodule update --init --recursive; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	@rm -rf $(OBJ_DIR)
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi

fclean: clean
	@rm -f $(NAME)
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -C $(LIBFT_DIR) fclean; fi

re: fclean all

test_forks: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./$(NAME)

test: re
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

test_r:
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

submodules:
	@echo "\033[0;33mInitializing submodules...\033[0m"
	@git submodule update --init --recursive

help:
	@echo "\033[0;32mAvailable targets:\033[0m"
	@echo "  \033[0;34mall\033[0m         - Build the project (default target)"
	@echo "  \033[0;34mclean\033[0m       - Remove object files"
	@echo "  \033[0;34mfclean\033[0m      - Remove object files and executable"
	@echo "  \033[0;34mre\033[0m          - Clean and rebuild"
	@echo "  \033[0;34msubmodules\033[0m  - Initialize/update git submodules"
	@echo "  \033[0;34mtest\033[0m        - Run with valgrind"
	@echo "  \033[0;34mtest_forks\033[0m  - Run with valgrind (trace children)"
	@echo "  \033[0;34mhelp\033[0m        - Show this help message"

.PHONY: all clean fclean re submodules help
