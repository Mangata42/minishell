/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:51:08 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/31 11:44:48 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_list	*init_ast_list(void)
{
	t_ast_list	*new_t_list;

	new_t_list = malloc(sizeof(t_ast_list));
	if (!new_t_list)
		return (NULL);
	new_t_list->first = NULL;
	new_t_list->last = NULL;
	new_t_list->size = 0;
	return (new_t_list);
}

t_ast_node	*create_ast_node(const char *value, t_token_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

void	free_ast_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	free(node);
}

void	free_ast_list(t_ast_list *list)
{
	t_ast_node	*current;
	t_ast_node	*next;

	if (!list)
		return ;
	current = list->first;
	while (current)
	{
		next = current->right;
		free_ast_node(current);
		current = next;
	}
	free(list);
}
