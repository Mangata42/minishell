/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:48:27 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 14:09:28 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/debugger.h"

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

void print_token_list(t_token_list *TokenList)
{
    t_token *TokenCursor;
    unsigned int index = 0;

    if (!TokenList || !TokenList->First)
    {
        printf(RED "Token list is empty.\n" RESET);
        return;
    }

    printf(CYAN "\n== TOKEN LIST (" YELLOW "%u" CYAN " tokens) ==\n" RESET, TokenList->size);

    TokenCursor = TokenList->First;
    while (TokenCursor)
    {
        printf(BLUE "Token %u:\n" RESET, index);
        printf("  " MAGENTA "Type   : " RESET);
        
        switch (TokenCursor->type)
        {
            case TOKEN_COMMAND:        printf(GREEN "Command" RESET); break;
            case TOKEN_ARGUMENT:       printf(GREEN "Argument" RESET); break;
            case TOKEN_PIPE:           printf(YELLOW "Pipe" RESET); break;
            case TOKEN_REDIRECTION_IN: printf(YELLOW "Redirection In" RESET); break;
            case TOKEN_REDIRECTION_OUT:printf(YELLOW "Redirection Out" RESET); break;
            case TOKEN_APPEND:         printf(YELLOW "Append" RESET); break;
            case TOKEN_HEREDOC:        printf(YELLOW "Heredoc" RESET); break;
            case TOKEN_VARIABLE:       printf(CYAN "Variable" RESET); break;
            case TOKEN_STRING:         printf(CYAN "String" RESET); break;
            case TOKEN_AND:            printf(CYAN "And" RESET); break;
            case TOKEN_OR:             printf(CYAN "Or" RESET); break;
            case TOKEN_EOF:            printf(MAGENTA "End of File" RESET); break;
            case TOKEN_WILDCARDS:      printf(MAGENTA "Wildcard" RESET); break;
            case TOKEN_EXPAND:         printf(MAGENTA "Expand" RESET); break;
            default:                   printf(RED "Unknown token type" RESET); break;
        }

        printf("\n  " MAGENTA "Value  : " RESET "\"%s\"\n", TokenCursor->value);
        printf(CYAN "-----------------------------\n" RESET);

        TokenCursor = TokenCursor->Next;
        index++;
    }

    printf(CYAN "== END OF TOKEN LIST ==\n\n" RESET);
}
