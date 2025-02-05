/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/02/05 16:03:59 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (type_of_operator(current->content) != 10 && type_of_operator(current->content) != 0)
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
		else if (type_of_operator(current->content) == 10)
		{
			if (!current->next)
				return (left);
			*tokens = current->next;
			right = parse_tokens(tokens);
			left = create_operator_node(PIPE_TYPE, left, right);
			break ;
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
	int		v;
	char	**argvtmp;
	char	**args;
	t_vars	vars;
	char	**arggs;

	init(&vars);
	args = malloc(2 * sizeof(char *));
	args[0] = ft_strdup("ABCD=hi");
	args[1] = NULL;
	arggs = malloc(3 * sizeof(char *));
	arggs[0] = ft_strdup("-n");
	arggs[1] = ft_strdup("qwer");
	arggs[2] = NULL;
	v = argc;
	argvtmp = argv;
	v++;
	argvtmp++;
	create_env_list(&(vars.env_list), env);
	ft_export(vars.env_list, NULL);
	ft_export(vars.env_list, args);
	ft_export(vars.env_list, arggs);
	printf("\n");
	ft_export(vars.env_list, NULL);
	ft_pwd(vars.env_list);
	ft_echo(arggs);
	printf("\n\n\n");
	vars.tokens = tokenize(&vars, argv[1]);
	// char	str[100] = "cat >> EOF | ";
	// t_list	*tokens;
	// t_node	*route;
	// tokens = tokenize(str);
	// print_list(tokens);
	// printf("\n");
	vars.node_list = parse_tokens(&vars.tokens);
	print_tree(vars.node_list, 0);
	free_vars(&vars);
}
