/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:05:11 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/11 03:58:02 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/debugger.h"
#include "../../include/minishell.h"

void	print_ast(t_ast_node *node, int level)
{
	if (!node)
		return ;
	print_indentation(level);
	print_node_info(node, level);
	if (node->left)
		print_ast(node->left, level + 1);
	if (node->right)
		print_ast(node->right, level + 1);
}

void	print_env_debug(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	print_indentation(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		printf("    ");
		i++;
	}
}

void	print_node_type(t_ast_node *node)
{
	if (node->type == AST_COMMAND)
		printf("COMMAND: ");
	else if (node->type == AST_PIPE)
		printf("PIPE\n");
	else if (node->type == AST_AND)
		printf("AND (&&)\n");
	else if (node->type == AST_OR)
		printf("OR (||)\n");
	else if (node->type == AST_REDIRECTION_IN)
		printf("REDIR_IN: <%s\n", node->filename);
	else if (node->type == AST_REDIRECTION_OUT)
		printf("REDIR_OUT: >%s\n", node->filename);
	else if (node->type == AST_REDIRECTION_APPEND)
		printf("REDIR_APPEND: >>%s\n", node->filename);
	else if (node->type == AST_REDIRECTION_HEREDOC)
		printf("HEREDOC: <<%s\n", node->filename);
}

void	print_node_info(t_ast_node *node, int level)
{
	const char	*color;
	int			i;

	color = get_color(level);
	printf("%s", color);
	print_node_type(node);
	if (node->type == AST_COMMAND && node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			printf("%s", node->argv[i]);
			if (node->argv[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	printf(RESET);
}

void	print_ast_node(t_ast_node *node)
{
	if (!node)
	{
		printf("Node is NULL\n");
		return ;
	}
	printf("Node type: %d\n", node->type);
	printf("Node argv: ");
	if (node->argv)
	{
		for (int i = 0; node->argv[i]; i++)
		{
			printf("%s ", node->argv[i]);
		}
		printf("\n");
	}
	else
	{
		printf("NULL\n");
	}
	printf("Node filename: %s\n", node->filename ? node->filename : "NULL");
	printf("Node left: %p\n", (void *)node->left);
	printf("Node right: %p\n", (void *)node->right);
	printf("Node shell: %p\n", (void *)node->shell);
}
