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

# Check for dependencies
check_deps:
	@echo "🔍 Checking dependencies..."
	@if ! brew --version >/dev/null 2>&1; then \
		echo "❌ Error: Homebrew is not installed. Please install Homebrew first:"; \
		echo "/bin/bash -c \"\$$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""; \
		exit 1; \
	fi
	@if ! command -v conda >/dev/null 2>&1; then \
		echo "📦 Miniconda not found. Installing miniconda..."; \
		brew install --cask miniconda; \
		echo "✅ Miniconda installed successfully!"; \
		echo "⚠️  Please restart your terminal or run: source ~/.zshrc"; \
	fi
	@if ! find /opt/homebrew/Caskroom/miniconda/base/lib -name "libreadline*" >/dev/null 2>&1; then \
		echo "❌ Readline library not found in miniconda. Please check your miniconda installation."; \
		exit 1; \
	fi
	@echo "✅ All dependencies are available!"

# Detect readline library location
READLINE_PATH := $(shell if [ -d "/opt/homebrew/Caskroom/miniconda/base/lib" ]; then echo "/opt/homebrew/Caskroom/miniconda/base/lib"; elif [ -d "/opt/homebrew/opt/readline/lib" ]; then echo "/opt/homebrew/opt/readline/lib"; else echo ""; fi)

$(NAME): check_deps $(LIBFT) $(OBJ) $(HEADERS)
	@echo "🔗 Linking $(NAME)..."
	@if [ -n "$(READLINE_PATH)" ]; then \
		$(CC) $(CFLAGS) -I inc -I libft/inc -I get_next_line/inc -o $(NAME) $(OBJ) $(LIBFT) -L$(READLINE_PATH) -Wl,-rpath,$(READLINE_PATH) -lreadline -lncurses; \
	else \
		$(CC) $(CFLAGS) -I inc -I libft/inc -I get_next_line/inc -o $(NAME) $(OBJ) $(LIBFT) -lreadline -lncurses; \
	fi

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I inc -I libft/inc -I get_next_line/inc -c $< -o $@

$(OBJ_DIR): $(HEADERS)
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@if [ ! -f $(LIBFT_DIR)/Makefile ]; then \
		echo "🔄 Initializing git submodules..."; \
		git submodule update --init --recursive; \
		echo "🔍 Verifying submodules are properly initialized..."; \
		if [ ! -f "libft/Makefile" ]; then \
			echo "⚠️  libft not properly initialized, retrying..."; \
			git submodule update --init libft; \
		fi; \
		if [ ! -f "get_next_line/src/get_next_line.c" ]; then \
			echo "⚠️  get_next_line not properly initialized, retrying..."; \
			git submodule update --init get_next_line; \
		fi; \
		echo "✅ All submodules ready!"; \
	fi
	@echo "🔨 Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@echo "✅ libft built successfully!"

clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi
	@echo "✅ Clean completed!"

fclean: clean
	@echo "🗑️  Removing executable..."
	@rm -f $(NAME)
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -C $(LIBFT_DIR) fclean; fi
	@echo "✅ Full clean completed!"

re: fclean all

test_forks: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./$(NAME)

test: re
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

test_r:
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

submodules:
	@echo "🔄 Initializing git submodules..."
	@git submodule update --init --recursive
	@echo "🔍 Verifying submodules are properly initialized..."
	@if [ ! -f "libft/Makefile" ]; then \
		echo "⚠️  libft not properly initialized, retrying..."; \
		git submodule update --init libft; \
	fi
	@if [ ! -f "get_next_line/src/get_next_line.c" ]; then \
		echo "⚠️  get_next_line not properly initialized, retrying..."; \
		git submodule update --init get_next_line; \
	fi
	@echo "✅ All submodules ready!"

help:
	@echo "📖 Available targets:"
	@echo "  🎯 all         - Build the project (default target)"
	@echo "  🔍 check_deps  - Check and install dependencies"
	@echo "  🧹 clean       - Remove object files"
	@echo "  🗑️  fclean      - Remove object files and executable"
	@echo "  🔄 re          - Clean and rebuild"
	@echo "  📦 submodules  - Initialize/update git submodules"
	@echo "  🧪 test        - Run with valgrind"
	@echo "  🧪 test_forks  - Run with valgrind (trace children)"
	@echo "  📖 help        - Show this help message"

.PHONY: all clean fclean re submodules help check_deps
