/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:48:58 by mratke            #+#    #+#             */
/*   Updated: 2025/02/27 19:07:21 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execute_node_prepare(t_vars *vars, t_node *node)
{
	if (!node)
		return (1);
	if (((node->type == REDIRECT_TYPE) || (node->type == COMMAND_TYPE))
		&& ((node->command_args == NULL) || ((node->command_args)[0] == NULL)))
	{
		vars->return_code = 258;
		return (error_message(node, 258), 258);
	}
	if ((node->command_args != NULL) && (node->command_args[0] != NULL)
		&& (ft_strcmp("<<", node->command_args[0]) != 0))
		expansion(vars, node->command_args);
	return (0);
}

static int	execute_or_and(t_vars *vars, t_node *node)
{
	if (execute_node(vars, node->left))
		return (ERR_SYNTAX);
	wait_childs(vars);
	if ((node->type == OR_TYPE) && (vars->return_code != 0))
	{
		if (execute_node(vars, node->right))
			return (ERR_SYNTAX);
	}
	else if ((node->type == AND_TYPE) && (vars->return_code == 0))
	{
		if (execute_node(vars, node->right))
			return (ERR_SYNTAX);
	}
	return (0);
}

int	execute_node(t_vars *vars, t_node *node)
{
	if (execute_node_prepare(vars, node) != 0)
		return (1);
	if (node->type == COMMAND_TYPE)
	{
		if (node->command_args == NULL)
			return (error_message(node, 258), ERR_SYNTAX);
		execute_command(vars, node, node->command_args);
	}
	else if (node->type == REDIRECT_TYPE)
	{
		if (execute_redirect(vars, node) != 0)
			return (258);
	}
	else if (node->type == PIPE_TYPE)
		pipe_redirect(vars, node);
	else if ((node->type == OR_TYPE) || (node->type == AND_TYPE))
	{
		if (execute_or_and(vars, node) != 0)
			return (ERR_SYNTAX);
	}
	return (0);
}

int	execute_tree(t_vars *vars, char *cmnd)
{
	vars->tokens = tokenize(vars, cmnd);
	if (ft_lstsize(vars->tokens) < 1)
		return (free_list(&(vars->tokens)), 0);
	add_history(cmnd);
	vars->node_list = parse_tokens(vars->tokens);
	if (execute_node(vars, vars->node_list))
		return (reset_vars(vars), ERR_SYNTAX);
	wait_childs(vars);
	reset_vars(vars);
	return (0);
}
