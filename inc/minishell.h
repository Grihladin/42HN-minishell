/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:31:01 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 11:41:05 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
#define PROMPT "⚡️ minishell ⚡️ ➜ "
#define PROMPT_HERE_DOC "> "

#include "get_next_line.h"
#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>

// Readline function declaration for compatibility
void rl_replace_line(const char *text, int clear_undo);
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#define ERR_NOT_FOUND 127
#define ERR_NO_PERM 126
#define ERR_SYNTAX 2
#define ERR_GENERAL 1
#define ERR_SYNTAX_NEAR 258
#define ERR_HEADER "minishell: "
#define MAX_FD 12288

extern sig_atomic_t g_signal_received;
// command type declaration

typedef enum s_node_type {
  COMMAND_TYPE,
  AND_TYPE,
  OR_TYPE,
  PIPE_TYPE,
  REDIRECT_TYPE,
} t_node_type;

// AST tree node declaration

// node type (one of t_node_type)
// arguments including flags
// left means left from pipe or && or ||
// same logic but right side

typedef struct s_node {
  t_node_type type;
  char **command_args;
  char **env;
  int *new_fds;
  int *old_fds;
  pid_t command_pid;
  struct s_node *left;
  struct s_node *right;
} t_node;

typedef struct s_env_list {
  char *key;
  char *value;
  struct s_env_list *next;
} t_env_list;
// env

t_env_list *ft_new_env(char *variable, char *value);
void ft_envadd_back(t_env_list **head, t_env_list *new_node);
void create_env_list(t_env_list **head, char **env);
int ft_env(t_env_list *head);
int env_lstsize(t_env_list *lst);
char *find_var_env(t_env_list *head, char *var);

// All main variables
typedef struct s_vars {
  t_env_list *env_list;
  t_node *node_list;
  t_list *paths;
  t_list *tokens;
  t_list *here_doc_buf;
  char **operators;
  struct sigaction sa;
  struct termios term;
  t_list *forks;
  int *old_fds;
  int cmnd_nmbrs;
  int return_code;
  pid_t last_pid;
  char im_in_pipe;
  int fd_stdin;
  int fd_stdout;
} t_vars;

// initialisation

int init(t_vars *vars, int argc, char **argv, char **env);

// ft_echo

int ft_echo(char **args);

// ft_cd

int ft_cd(t_vars *vars, char **args);

// ft_export

t_env_list *env_split_line(char *str);
t_env_list *is_in_env(t_env_list *head, char *arg);
int is_valid_var_name(char *str);
void print_env_export(t_env_list *sorted_env_list);
t_env_list *sort_env_list(t_env_list *head);
int ft_export(t_env_list **env, char **args);
void ft_envdel(t_env_list **lst, void (*del)(void *));

// sig handling

void set_signals(t_vars *vars);
void set_signal_child(t_vars *vars);
void heredoc_handler(int signum);
void set_signal_heredoc(t_vars *vars);
void set_signal_quit(t_vars *vars);
void set_signal_handler_parent(t_vars *vars);

// pipes and redirection

void write_list_to_fd(t_list *str_list, int fd);
int execute_redirect(t_vars *vars, t_node *node);
int l_redirect(t_vars *vars, t_node *node);
int ll_redirect(t_vars *vars, t_node *node);
int r_redirect(t_vars *vars, t_node *node);
int rr_redirect(t_vars *vars, t_node *node);
int pipe_redirect(t_vars *vars, t_node *node);
int compare_fds(int fd1, int fd2);

// getnextline
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

int is_in_str(char *s, char c);
char *ft_strdup(const char *src);
char *ft_str_merge(char *s1, char *s2);
int ft_strlen(const char *s);
char *line_validator(char *s);
char *read_and_merge(int fd, char *current_line);

int create_pipe(int **p);
int save_fds(int **fd);
int restore_fds(int **fd);
int close_fds(int **fd);

// prompt
int wait_command(t_vars *vars);

// pwd

int ft_pwd(t_env_list *env_list);

// ft_cd

int ft_cd(t_vars *vars, char **args);
void update_old_pwd(t_vars *vars, char *dir);
void update_pwd(t_vars *vars, char *dir);

// ft_unset

int ft_unset(t_vars *vars, char **args);

// ft_exit

int ft_exit(char **args, t_vars *vars);

// HERE_DOC

int here_doc(t_vars *vars, t_node *node, char expansion);

// tree functions

void clear_tree(t_node **root);
t_node *create_command_node(char **args);
t_node *create_operator_node(t_node_type type, t_node *left, t_node *right);
t_node *create_redirect_node(t_node *command, char *operator, char * file);
t_node *parse_tokens(t_list *tokens);
int type_of_operator(char *str);

// tokenization
t_list *tokenize(t_vars *vars, char *str);
char **copy_lst_to_arr(t_list **lst);
char *mv_lst_to_str(t_list **lst);
char *copy_token_to_str(char **str, char *end);

// expansion
char *handle_vars(t_vars *vars, char *instr);
char *handle_vars_heredoc(t_vars *vars, char *str);
int expansion(t_vars *vars, char **arr);
char *expansion_get_var(t_vars *vars, char **str, char quotes);
char *get_next_part_double_quotes(t_vars *vars, char **str);
char *get_next_part_single_quotes(char **str);

// paths

int get_paths(t_vars *vars);
char *get_full_path(char *path, t_list *lstpath);

// execution
int execute_tree(t_vars *vars, char *cmnd);
int execute_node(t_vars *vars, t_node *node);
int execute_command(t_vars *vars, t_node *node, char **args);

// user input

char *get_next_user_input(char *prompt);

// ast_utils
void populate_command_arguments(t_node *cmd_root, t_list **current,
                                int arg_count);
int count_command_arguments(t_list *iter);
t_node *handle_redirection(t_node *node, t_list **iter);
t_node *handle_invalid_redirection(t_node *node, char *oper, t_list **iter);
int is_control_operator(char *token);

// utils

int calculate_args(t_list *current);
int error_message(t_node *node, int error);
char *ft_strtolower(char *str);
void print_list(t_list *head);
void ft_lstprint_str(t_list *lst);
int add_str_to_list(char *str, struct s_list **lst);
int is_operator(char *str);
int type_of_operator(char *str);
int is_space(char str);
char *get_home(t_vars *vars);
char *token_end(char *str);
void free_double_array(char **arr);
void free_vars(t_vars *vars);
void free_list(t_list **lst);
void reset_vars(t_vars *vars);
void free_arr_of_str(char ***strings);
void delete_content(void *n);
int reset_stdio(t_vars *vars);
int close_all_fds(void);
char *delete_quotes(char *str);

char **env_to_array(t_env_list *env_lst);
int wait_childs(t_vars *vars);

#endif
