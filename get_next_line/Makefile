# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 15:32:34 by psenko            #+#    #+#              #
#    Updated: 2024/11/08 17:55:34 by psenko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=get_next_line.a
CFLAGS=-c -Wall -Wextra -Werror
SOURCES=get_next_line_bonus.c get_next_line_utils_bonus.c
OBJECTS=$(SOURCES:.c=.o)

all: $(OBJECTS)
	ar -rs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

$(NAME): all

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: all clean fclean re
