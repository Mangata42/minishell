/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:42 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/08 12:01:55 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
t_ast_node	*create_ast_node(t_ast_node_type type, t_sh *shell)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->argv = NULL;
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	node->shell = shell;
	return (node);
}

static char	**duplicate_argv(char **argv, int argc, char *argument)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(argument);
	new_argv[i + 1] = NULL;
	return (new_argv);
}

void	add_argument(t_ast_node *node, char *argument)
{
	char	**new_argv;
	int		argc;

	argc = 0;
	while (node->argv && node->argv[argc])
		argc++;
	new_argv = duplicate_argv(node->argv, argc, argument);
	if (!new_argv)
		return ;
	free(node->argv);
	node->argv = new_argv;
}

void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
	}
	if (node->filename)
		free(node->filename);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}
