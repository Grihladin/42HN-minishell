/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/02/07 10:40:33 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_of_operator(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, "<<"))
		return (REDIRECT_TYPE);
	else if (!ft_strcmp(str, "|"))
		return (PIPE_TYPE);
	else if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||"))
		return (AND_OR_TYPE);
	return (0);
}

// temporary solution because i need an array of strings in command.
static t_node	*handle_command(t_list **current)
{
	int		arg_count;
	t_list	*temp;
	char	**args;
	int		i;

	i = 0;
	arg_count = 0;
	temp = *current;
	while (temp && !type_of_operator(temp->content))
	{
		arg_count++;
		temp = temp->next;
	}
	args = malloc((arg_count + 1) * sizeof(char *));
	while (i < arg_count)
	{
		args[i] = ft_strdup((*current)->content);
		if (!args[i])
			return (free_double_array(args), NULL);
		*current = (*current)->next;
		i++;
	}
	args[arg_count] = NULL;
	return (create_command_node(args));
}

//Level 1 (&&):        &&
//                   /    \
//Level 2 (|):    cmd1    |
//                     /   \
//Level 3 (>):      cmd2   cmd3 > file
t_node	*parse_tokens(t_list **tokens)
{
	t_node	*left;
	t_list	*current;
	t_node	*right;
	char	*file;
	char	*oper;

	if (!tokens || !*tokens)
		return (NULL);
	left = NULL;
	current = *tokens;
	while (current)
	{
		if (type_of_operator(current->content) == AND_OR_TYPE)
		{
			if (!current->next)
				return (left);
			*tokens = current->next;
			right = parse_tokens(tokens);
			left = create_operator_node(AND_OR_TYPE, left, right);
			break ;
		}
		else if (type_of_operator(current->content) == PIPE_TYPE)
		{
			if (!current->next)
				return (left);
			*tokens = current->next;
			right = parse_tokens(tokens);
			left = create_operator_node(PIPE_TYPE, left, right);
			break ;
		}
		else if (type_of_operator(current->content) == REDIRECT_TYPE)
		{
			oper = ft_strdup(current->content);
			if (!current->next)
			{
				free(oper);
				return (left);
			}
			current = current->next;
			file = ft_strdup(current->content);
			left = create_redirect_node(left, oper, file);
			free(oper);
			free(file);
			current = current->next;
		}
		else
		{
			left = handle_command(&current);
			if (!left)
				return (NULL);
		}
	}
	*tokens = current;
	return (left);
}

// dont test with && or || not implemented yet
int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	// char	**env_arr;
	if (!init(&vars, argc, argv, env))
	{
		wait_command(&vars);
	}
	// char	str[100] = "cat >> EOF | ";
	// t_list	*tokens;
	// t_node	*route;
	// tokens = tokenize(str);
	// print_list(tokens);
	// printf("\n");
	// env_arr = env_to_array(&vars);
	// free_arr_of_str(&env_arr);
	free_vars(&vars);
	return (0);
}
