NAME	:= minishell

#################################
#			Config				#
#################################

CC	:= gcc

#################################
#			Flags				#
#################################

DEBUG_FLAGS	:= -g -fsanitize=address -fsanitize=undefined -O0
CFLAGS		:= -Wall -Wextra -Werror

#################################
#			Files				#
#################################

SRC = \
main.c \
init.c \
pipes.c \
prompt.c \
execute.c \
get_path.c \
here_doc.c \
free_vars.c \
expansion.c \
user_input.c \
list_to_arr.c \
wait_childs.c \
tokenization.c \
execute_tree.c \
env_to_array.c \
utils/utils.c \
utils/utils1.c \
utils/utils2.c \
utils/utils3.c \
execute_pipe.c \
expansion_quotes.c \
execute_redirect.c \
expansion_heredoc.c \
expansion_get_var.c \
ast_tree/ast_build.c \
ast_tree/ast_utils.c \
ast_tree/ast_nodes.c \
signals/sig_actions.c \
builtins/ft_cd/ft_cd.c \
builtins/ft_pwd/ft_pwd.c \
builtins/ft_env/ft_env.c \
builtins/ft_echo/ft_echo.c \
signals/sig_actions_quit.c \
builtins/ft_exit/ft_exit.c \
builtins/ft_unset/ft_unset.c \
builtins/ft_cd/ft_cd_utils.c \
builtins/ft_export/ft_export.c \
builtins/ft_env/ft_env_utils.c \
signals/sig_actions_here_doc.c \
builtins/ft_export/ft_export_utils.c \
builtins/ft_export/ft_export_utils1.c \

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

GET_NEXT_LINE_DIR = get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/get_next_line.a

HEADERS = minishell.h

OBJ_DIR = objects
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

#################################
#			Rules				#
#################################

all: $(NAME)
	@echo "\033[0;32m$(NAME) built successfully!\033[0m"

$(NAME): $(LIBFT) $(GET_NEXT_LINE) $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(GET_NEXT_LINE) -lreadline -lncurses

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR): $(HEADERS)
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(GET_NEXT_LINE):
	@$(MAKE) -C $(GET_NEXT_LINE_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean

re: fclean all

test_forks: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./$(NAME)

test: re
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

test_r:
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re
