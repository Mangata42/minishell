/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:26:37 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/19 13:33:25 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_append_solo(t_token *redir_in_token)
{
	open(redir_in_token->next->value, O_CREAT | O_RDWR, 0666);
	redir_in_token->type = TOKEN_ARGUMENT;
	redir_in_token->next->type = TOKEN_ARGUMENT;
	free(redir_in_token->value);
	redir_in_token->value = ft_strdup("test");
}

int	check_redir_next_token(t_token *redir_in_token, int check_mask)
{
	t_token_type	n_type;

	n_type = redir_in_token->next->type;
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

int	handle_token_append_case(t_token *redir_in_token)
{
	if (!redir_in_token->prev
		|| (redir_in_token->prev->type & (TOKEN_AND | TOKEN_OR | TOKEN_LPAREN)))
	{
		handle_append_solo(redir_in_token);
		return (1);
	}
	return (0);
}

int	verif_redir_in_out_set(t_token *redir_in_token)
{
	int	check_mask;

	if (!redir_in_token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (redir_in_token->type == TOKEN_APPEND)
	{
		if (handle_token_append_case(redir_in_token))
			return (0);
	}
	check_mask = TOKEN_STRING | TOKEN_COMMAND | TOKEN_EXPAND | TOKEN_ARGUMENT;
	return (check_redir_next_token(redir_in_token, check_mask));
}
