/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:45 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/05 18:02:24 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*ast_parser(t_t_list *token_list, t_sh *shell)
{
	t_token		*current_token;
	t_ast_node	*ast_root;

	current_token = token_list->first;
	ast_root = parse_and_or_sequence(&current_token, shell);
	return (ast_root);
}

t_ast_node	*parse_and_or_sequence(t_token **current_token, t_sh *shell)
{
	t_ast_node	*left;
	t_ast_node	*node;
	t_token		*token;

	left = parse_pipeline(current_token, shell);
	while (*current_token
		&& ((*current_token)->type == TOKEN_AND
			|| (*current_token)->type == TOKEN_OR))
	{
		token = *current_token;
		*current_token = (*current_token)->next;
		node = create_ast_node(AST_AND, shell);
		if (token->type == TOKEN_OR)
		{
			node->type = AST_OR;
		}
		node->left = left;
		node->right = parse_pipeline(current_token, shell);
		left = node;
	}
	return (left);
}
