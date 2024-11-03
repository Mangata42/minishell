/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:45 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/03 17:17:18 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	chain_redirection(t_ast_node *command_node, t_ast_node *redir_node)
{
	t_ast_node	*tmp;

	if (!command_node->left)
		command_node->left = redir_node;
	else
	{
		tmp = command_node->left;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = redir_node;
	}
}

t_ast_node	*create_redirection_node(t_token_type type)
{
	t_ast_node	*redir_node;

	redir_node = NULL;
	if (type == TOKEN_HEREDOC)
		redir_node = create_ast_node(AST_REDIRECTION_HEREDOC);
	else if (type == TOKEN_REDIRECTION_OUT)
		redir_node = create_ast_node(AST_REDIRECTION_OUT);
	else if (type == TOKEN_APPEND)
		redir_node = create_ast_node(AST_REDIRECTION_APPEND);
	else if (type == TOKEN_REDIRECTION_IN)
		redir_node = create_ast_node(AST_REDIRECTION_IN);
	return (redir_node);
}

int	handle_heredoc_error(t_token **current_token)
{
	printf("minishell: syntax error near unexpected token `newline`\n");
	*current_token = NULL;
	return (0);
}

int	process_redirection(t_token **current_token, t_ast_node *command_node)
{
	t_ast_node	*redir_node;
	t_token		*token;

	token = *current_token;
	*current_token = (*current_token)->next;
	if (token->type == TOKEN_HEREDOC && (!*current_token || \
			(*current_token)->type != TOKEN_STRING))
		return (handle_heredoc_error(current_token));
	redir_node = create_redirection_node(token->type);
	if (redir_node)
	{
		redir_node->filename = ft_strdup(token->value);
		chain_redirection(command_node, redir_node);
	}
	return (1);
}

void	parse_redirections(t_token **current_token, t_ast_node *command_node)
{
	while (*current_token && ((*current_token)->type == TOKEN_REDIRECTION_IN || \
			(*current_token)->type == TOKEN_REDIRECTION_OUT || \
			(*current_token)->type == TOKEN_APPEND || \
			(*current_token)->type == TOKEN_HEREDOC))
	{
		if (!process_redirection(current_token, command_node))
			return ;
	}
}
