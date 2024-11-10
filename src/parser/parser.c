/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:48:46 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/10 21:53:08 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verif_redir_in_out_set(t_token *redir_in_token)
{
	t_token_type	n_type;
	int				check_mask;

	if (!redir_in_token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	n_type = redir_in_token->next->type;
	check_mask = TOKEN_STRING | TOKEN_COMMAND | TOKEN_EXPAND | TOKEN_ARGUMENT;
	if (!(n_type & check_mask))
	{
		if (redir_in_token->next)
			printf("minishell: syntax error near unexpected token `%s'\n",
				redir_in_token->next->value);
		else
			printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	verif_operand_set(t_token *operand_token)
{
	t_token_type	p_type;
	int				check_mask;

	if (!operand_token->index || !operand_token->next)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			operand_token->value);
		return (1);
	}
	p_type = operand_token->prev->type;
	check_mask = (TOKEN_ARGUMENT | TOKEN_STRING
			| TOKEN_WILDCARDS | TOKEN_EXPAND
			| TOKEN_COMMAND | TOKEN_RPAREN);
	if (!(p_type & check_mask))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			operand_token->value);
		return (1);
	}
	return (0);
}

int	check_parentheses_balance(t_t_list *token_list)
{
	t_token	*current_token;
	int		balance;

	current_token = token_list->first;
	balance = 0;
	while (current_token)
	{
		if (current_token->type == TOKEN_LPAREN)
			balance++;
		else if (current_token->type == TOKEN_RPAREN)
			balance--;
		if (balance < 0)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				current_token->value);
			return (1);
		}
		current_token = current_token->next;
	}
	if (balance != 0)
	{
		printf("minishell: syntax error: unmatched parentheses\n");
		return (1);
	}
	return (0);
}

int	check_token_type(t_token *token)
{
	int	status;

	status = 0;
	if (token->type == TOKEN_PIPE)
		status = verif_pipe(token);
	else if (token->type & (TOKEN_REDIRECTION_IN
			| TOKEN_HEREDOC | TOKEN_REDIRECTION_OUT
			| TOKEN_APPEND))
		status = verif_redir_in_out_set(token);
	else if (token->type & (TOKEN_AND | TOKEN_OR))
		status = verif_operand_set(token);
	else if (token->type == TOKEN_RPAREN)
		status = verif_rparen(token);
	return (status);
}

int	parser(t_t_list *token_list)
{
	t_token	*token_cursor;
	int		status;

	if (!token_list->size)
		return (1);
	token_cursor = token_list->first;
	status = 0;
	if (check_parentheses_balance(token_list))
		return (1);
	while (token_cursor)
	{
		status = check_token_type(token_cursor);
		if (status)
			return (status);
		token_cursor = token_cursor->next;
	}
	return (0);
}
// int	parser(t_t_list *token_list)
// {
// 	t_token	*token_cursor;
// 	int		status;

// 	if (!token_list->size)
// 		return (1);
// 	token_cursor = token_list->first;
// 	status = 0;
// 	if (check_parentheses_balance(token_list))
// 		return (1);
// 	while (token_cursor)
// 	{
// 		if (token_cursor->type == TOKEN_PIPE)
// 			status = verif_pipe(token_cursor);
// 		else if (token_cursor->type & (TOKEN_REDIRECTION_IN
		// | TOKEN_HEREDOC | TOKEN_REDIRECTION_OUT | TOKEN_APPEND))
// 			status = verif_redir_in_out_set(token_cursor);
// 		else if (token_cursor->type & (TOKEN_AND | TOKEN_OR))
// 			status = verif_operand_set(token_cursor);
// 		else if (token_cursor->type == TOKEN_RPAREN)
// 			status = verif_rparen(token_cursor);
// 		else if (token_cursor->type == TOKEN_INCONNU)
// 			status = verif_unknown(token_cursor);
// 		if (status)
// 			return (status);
// 		token_cursor = token_cursor->next;
// 	}
// 	return (0);
// }

// int	verif_unknown(t_token *unknown_token)
// {
// 	// printf("minishell: syntax error near unexpected token : `%s'\n",
// 	// 	unknown_token->value);
// 	return (1);
// }
