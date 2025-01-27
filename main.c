/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/01/27 18:22:19 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_list	*head;
	// char	str[100] = "echo\"\"\"\"\"\"Hello      && ls -l | ls grep \" file \"";
	char	str[100] = "echo hi | cat << eof ";

	// t_node	*echo_node;
	// t_node	*ls_node;
	// t_node	*grep_node;
	// t_node	*and_node1;
	// t_node	*root;
	head = tokenize(str);
	print_list(head);
	// char	*echo_cmd[] = {"echo", "Hello", NULL};
	// char	*ls_cmd[] = {"ls", "-l", NULL};
	// char	*grep_cmd[] = {"grep", "file", NULL};
	// echo_node = create_command_node(echo_cmd);
	// ls_node = create_command_node(ls_cmd);
	// grep_node = create_command_node(grep_cmd);
	// and_node1 = create_operator_node(AND_TYPE, echo_node, ls_node);
	// root = create_operator_node(AND_TYPE, and_node1, grep_node);
	// print_tree(root, 4);
}
