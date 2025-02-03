/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:31:01 by mratke            #+#    #+#             */
/*   Updated: 2025/02/03 22:25:18 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// command type declaration

typedef enum s_node_type
{
	COMMAND_TYPE,
	PIPE_TYPE,
	REDIRECT_TYPE,
	OR_TYPE,
	AND_TYPE
}						t_node_type;

// AST tree node declaration

// node type (one of t_node_type)
// arguments including flags
// left means left from pipe or && or ||
// same logic but right side

typedef struct s_node
{
	t_node_type			type;
	char				**command_args;
	char				**env;
	pid_t				command_pid;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;
// env

t_env_list				*ft_new_env(char *variable, char *value);
void					ft_envadd_back(t_env_list **head, t_env_list *new_node);
void					create_env_list(t_env_list **head, char **env);
void					print_env_list(t_env_list *head);
char					*find_var_env(t_env_list *head, char *var);

// All main variables
typedef struct s_vars
{
	t_env_list			*env_list;
	t_node				*node_list;
	struct s_list		*paths;
	t_list				*tokens;
	char				**operators;
}						t_vars;

void					init(t_vars *vars);

// export

void					print_env_export(t_env_list *sorted_env_list);
t_env_list				*sort_env_list(t_env_list *head);
void					ft_export(t_env_list *env, char **args);
void					ft_envdel(t_env_list **lst, void (*del)(void *));

//pwd
void	ft_pwd(t_env_list *env_list);


// tree functions

t_node					*create_command_node(char **args);
t_node					*create_operator_node(t_node_type type, t_node *left,
							t_node *right);
t_node					*create_redirect_node(t_node *command, char *operator,
							char * file);

// tokenization
t_list					*tokenize(t_vars *vars, char *str);
char					**copy_lst_to_arr(t_list **lst);
// int					get_paths(char **envp, struct s_paths *paths);

// utils
void					print_list(t_list *head);
void					print_tree(t_node *root, int depth);
int						is_operator(char *str);
int						is_space(char *str);
size_t					token_len(char *str);
void					free_double_array(char **arr);
void					free_vars(t_vars *vars);
void					free_list(t_list **lst);

#endif
