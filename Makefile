NAME	:= minishell

#################################
#			Config				#
#################################

CC	:= gcc

#################################
#			Flags				#
#################################

DEBUG_FLAGS	:= -g -fsanitize=address -fsanitize=undefined -O0
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=address

#################################
#			Files				#
#################################

SRC = \
main.c \
tokenization.c \
utils.c \
ast_nodes.c \
ast_build.c \
ft_cd.c \
ft_env.c \
ft_pwd.c \
ft_echo.c \
ft_unset.c \
ft_export.c \
ft_export_utils.c \
ft_exit.c \
list_to_arr.c \
free_vars.c \
init.c \
env_var.c \
utils1.c \
get_path.c \
env_to_array.c \
prompt.c \
sig_actions.c \
execute.c \
execute_tree.c \
pipes.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADERS = minishell.h

OBJ_DIR = objects
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

#################################
#			Rules				#
#################################

all: $(NAME)
	@echo "\033[0;32m$(NAME) built successfully!\033[0m"

$(NAME): $(LIBFT) $(OBJ) $(HEADERS)
	@$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
