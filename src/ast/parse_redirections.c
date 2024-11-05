/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:45 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/05 10:16:10 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirection_token(t_token *token)
{
	return (token && (token->type == TOKEN_REDIRECTION_IN
			|| token->type == TOKEN_REDIRECTION_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC));
}

void	parse_redir(t_token **curr_tok, t_ast_node *cmd_node, t_sh *shell)
{
	t_token		*token;
	t_ast_node	*redir_node;
	t_ast_node	*tmp;

	while (is_redirection_token(*curr_tok))
	{
		token = *curr_tok;
		*curr_tok = (*curr_tok)->next;
		if (!*curr_tok ||
			((*curr_tok)->type != TOKEN_ARGUMENT
				&& (*curr_tok)->type != TOKEN_HEREDOC
				&& (*curr_tok)->type != TOKEN_STRING // Ajoutez cette condition
				&& (*curr_tok)->prev->type != TOKEN_ARGUMENT))
		{
			if (*curr_tok != NULL)
				printf("minishell: %s: Aucun fichier ou dossier de ce type\n",
					(*curr_tok)->value);
			else
				printf("minishell: Aucun fichier ou dossier de ce type\n");
					// TODO: je ne sais pas si on garde cette erreur
			shell->exit_status = 1;
			return ;
		}
		if (token->type == TOKEN_REDIRECTION_IN)
		{
			printf("\n\nredirection in\n\n");
			redir_node = create_ast_node(AST_REDIRECTION_IN, shell);
		}
		if (token->type == TOKEN_REDIRECTION_OUT)
		{
			printf("\n\nredirection out\n\n");
			redir_node = create_ast_node(AST_REDIRECTION_OUT, shell);
		}
		else if (token->type == TOKEN_APPEND)
		{
			printf("\n\nredirection append\n\n");
			redir_node = create_ast_node(AST_REDIRECTION_APPEND, shell);
		}
		else if (token->type == TOKEN_HEREDOC)
		{
			printf("\n\nredirection heredoc\n\n");
			redir_node = create_ast_node(AST_REDIRECTION_HEREDOC, shell);
		}
		redir_node->filename = ft_strdup((*curr_tok)->value);
		*curr_tok = (*curr_tok)->next;
		if (!cmd_node->left)
			cmd_node->left = redir_node;
		else
		{
			tmp = cmd_node->left;
			while (tmp->left)
				tmp = tmp->left;
			tmp->left = redir_node;
		}
	}
}
