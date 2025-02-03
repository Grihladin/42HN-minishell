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
tokenization.c \
utils.c \
tree.c \
ft_env.c \
ft_export.c \
ft_export_utils.c \
list_to_arr.c \
free_vars.c \
init.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ_DIR = objects
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

#################################
#			Rules				#
#################################

all: $(NAME)
	@echo "\033[0;32m$(NAME) built successfully!\033[0m"

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

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
