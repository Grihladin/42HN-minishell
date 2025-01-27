/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:31:01 by mratke            #+#    #+#             */
/*   Updated: 2025/01/27 18:57:38 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// command type declaration

typedef enum s_node_type
{
	COMMAND_TYPE,
	PIPE_TYPE,
	REDIRECT_TYPE,
	OR_TYPE,
	AND_TYPE
}					t_node_type;

// AST tree node declaration

// node type (one of t_node_type)
// arguments including flags
// left means left from pipe or && or ||
// same logic but right side

typedef struct s_node
{
	t_node_type		type;
	char			**command_args;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

// tree functions

t_node				*create_command_node(char **args);
t_node				*create_operator_node(t_node_type type, t_node *left,
						t_node *right);
t_node				*create_redirect_node(t_node *command, char *operator, char
						*file);

// tokenization
t_list				*tokenize(char *str);

// utils
void				print_list(t_list *head);
void				print_tree(t_node *root, int depth);
void				free_double_array(char **arr);

#endif
