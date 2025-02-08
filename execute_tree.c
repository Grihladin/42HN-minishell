/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:48:58 by mratke            #+#    #+#             */
/*   Updated: 2025/02/08 12:39:53 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_node(t_vars *vars, t_node *node)
{
	if (!node)
		return ;
	if (node->type == COMMAND_TYPE)
	{
		// printf("Execute command: %s\n", node->command_args[0]);
		execute_command(vars, node, node->command_args);
		// printf("Execute command: %s\n", node->command_args[0]);
		// for (int i = 0; node->command_args[i]; i++)
		// 	printf("%s ", node->command_args[i]);
		// printf("\n");
	}
	else if (node->type == REDIRECT_TYPE)
	{
		// printf("Operator: REDIRECT\n");
		// for (int i = 0; node->command_args[i]; i++)
		// 	printf("%s ", node->command_args[i]);
		// printf("\n");
		execute_node(vars, node->left);
	}
	else
	{
		// printf("Operator: %s\n",
		// 	node->type == PIPE_TYPE ? "PIPE" : node->type == AND_TYPE ? "AND" : "OR");
		execute_node(vars, node->left);
		execute_node(vars, node->right);
	}
}

int	execute_tree(t_vars *vars, char *cmnd)
{
	// printf("Execute command: %s\n", cmnd);
	vars->tokens = tokenize(vars, cmnd);
	printf("Print tokens list:\n");
	print_list(vars->tokens);
	vars->node_list = parse_tokens(&(vars->tokens));
	// printf("Print tree\n");
	// print_tree(vars->node_list, 0);
	// printf("Execute tree\n");
	execute_node(vars, vars->node_list);
	// execute_programm(vars, cmnd);
	clear_tree(&(vars->node_list));
	free_list(&(vars->tokens));
	return (0);
}
