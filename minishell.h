/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:31:01 by mratke            #+#    #+#             */
/*   Updated: 2025/02/07 21:45:32 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define PROMPT "minishell: "

# include "libft/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// command type declaration

typedef enum s_node_type
{
	COMMAND_TYPE,
	AND_TYPE,
	OR_TYPE,
	PIPE_TYPE,
	REDIRECT_TYPE,
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
void					ft_env(t_env_list *head);
int						env_lstsize(t_env_list *lst);
char					*find_var_env(t_env_list *head, char *var);

// All main variables
typedef struct s_vars
{
	t_env_list			*env_list;
	t_node				*node_list;
	t_list				*paths;
	t_list				*tokens;
	char				**operators;
	struct sigaction	sigaction;
}						t_vars;

// initialisation

int						init(t_vars *vars, int argc, char **argv, char **env);

// ft_echo

void					ft_echo(char **args);

// ft_cd

void					ft_cd(t_vars *vars, char **args);

// export

int						is_valid_var_name(char *str);
void					print_env_export(t_env_list *sorted_env_list);
t_env_list				*sort_env_list(t_env_list *head);
void					ft_export(t_env_list *env, char **args);
void					ft_envdel(t_env_list **lst, void (*del)(void *));

// sig handling

void					set_sigs(t_vars *vars);

// prompt
int						wait_command(t_vars *vars);

// pwd

void					ft_pwd(t_env_list *env_list);

// ft_cd

void					ft_cd(t_vars *vars, char **args);

// ft_unset

void					ft_unset(t_vars *vars, char **args);

// tree functions

void					clear_tree(t_node *root);
t_node					*create_command_node(char **args);
t_node					*create_operator_node(t_node_type type, t_node *left,
							t_node *right);
t_node					*create_redirect_node(t_node *command, char *operator,
							char * file);
t_node					*parse_tokens(t_list **tokens);
int						type_of_operator(char *str);

// tokenization
t_list					*tokenize(t_vars *vars, char *str);
char					**copy_lst_to_arr(t_list **lst);
char					*copy_lst_to_str(t_list **lst);
char					*handle_env_var(t_vars *vars, char *str);
int						get_paths(t_vars *vars);

// execution
int						execute_command(t_vars *vars, char *cmnd);

// utils
void					print_list(t_list *head);
void					ft_lstprint_str(t_list *lst);
void					print_tree(t_node *root, int depth);
int						add_str_to_list(char *str, struct s_list **lst);
int						is_operator(char *str);
int						type_of_operator(char *str);
int						is_space(char *str);
size_t					token_len(char *str);
void					free_double_array(char **arr);
void					free_vars(t_vars *vars);
void					free_list(t_list **lst);
void					free_arr_of_str(char ***strings);
void					delete_content(void *n);

char					**env_to_array(t_vars *vars);

#endif
