/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:48:27 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 20:51:45 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_token_type(t_token_type type)
{
	switch (type)
	{
	case TOKEN_COMMAND:
		printf("Command: ");
		break;
	case TOKEN_ARGUMENT:
		printf("Argument: ");
		break;
	case TOKEN_PIPE:
		printf("Pipe: ");
		break;
	case TOKEN_REDIRECTION_IN:
		printf("Redirection In: ");
		break;
	case TOKEN_REDIRECTION_OUT:
		printf("Redirection Out: ");
		break;
	case TOKEN_APPEND:
		printf("Append: ");
		break;
	case TOKEN_HEREDOC:
		printf("Heredoc: ");
		break;
	case TOKEN_VARIABLE:
		printf("Variable: ");
		break;
	case TOKEN_STRING:
		printf("String: ");
		break;
	case TOKEN_AND:
		printf("And: ");
		break;
	case TOKEN_OR:
		printf("Or: ");
		break;
	case TOKEN_EOF:
		printf("End of File: ");
		break;
	case TOKEN_WILDCARDS:
		printf("Wildcard: ");
		break;
	case TOKEN_EXPAND:
		printf("Expand: ");
		break;
	default:
		printf("Unknown token type: ");
		break;
	}
}

void	print_token_list(t_token_list *TokenList)
{
	t_token *TokenCursor;

	TokenCursor = TokenList->First;
	while (TokenCursor)
	{
		print_token_type(TokenCursor->type);
		printf("%s\n", TokenCursor->value);
		TokenCursor = TokenCursor->Next;
	}
}
