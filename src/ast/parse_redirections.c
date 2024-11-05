/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:45 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/03 21:57:05 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirection_token(t_token *token)
{
	return (token && (token->type == TOKEN_REDIRECTION_IN
		|| token->type == TOKEN_REDIRECTION_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC));
}

void parse_redir(t_token **current_token, t_ast_node *command_node, t_sh *shell)
{
	t_token *token;
	t_ast_node *redir_node;
	t_ast_node *tmp;

	while (is_redirection_token(*current_token))
	{
		token = *current_token;
		*current_token = (*current_token)->next;
		if ((!*current_token 
		|| (*current_token)->type != TOKEN_ARGUMENT)
		&& !(*current_token)->type != TOKEN_HEREDOC )
		{
			printf("minishell: %s: Aucun fichier ou dossier de ce type\n", (*current_token)->value);
			shell->exit_status = 1;
			return;
		}
		redir_node = create_ast_node(AST_REDIRECTION_IN, shell);
		if (token->type == TOKEN_REDIRECTION_OUT)
			redir_node = create_ast_node(AST_REDIRECTION_OUT, shell);
		else if (token->type == TOKEN_APPEND)
			redir_node = create_ast_node(AST_REDIRECTION_APPEND, shell);
		else if (token->type == TOKEN_HEREDOC)
			redir_node = create_ast_node(AST_REDIRECTION_HEREDOC, shell);
		redir_node->filename = ft_strdup((*current_token)->value);
		*current_token = (*current_token)->next;
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
}
