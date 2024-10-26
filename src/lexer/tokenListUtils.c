/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenListUtils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:27:26 by nghaddar          #+#    #+#             */
/*   Updated: 2024/10/26 20:37:51 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_list *init_token_list()
{
	t_token_list *NewTokenList;

	NewTokenList = malloc(sizeof(t_token_list));
	if (!NewTokenList)
		return (NULL);
	
	NewTokenList->First = NULL;
	NewTokenList->Last = NULL;
	NewTokenList->size = 0;
	return (NewTokenList);
}


void free_token_list(t_token_list *TokenListToFree)
{
	t_token *TokenCursor;
	t_token *ToFree;

	if (TokenListToFree) // if TokenList actually exists
	{
		TokenCursor = TokenListToFree->First;
		while (TokenCursor)
		{
			ToFree = TokenCursor;
			TokenCursor = ToFree->Next;
			if (ToFree->value) // to avoid double free or non-malloc'ed values
				free(ToFree->value);
			free(ToFree);
		}
		free(TokenListToFree);
	}
}

t_token *create_token(const char *value, t_token_type type)
{
	t_token *NewToken = malloc(sizeof(t_token));

	if (!NewToken)
		return (NULL);
	
	NewToken->Next = NULL;
	NewToken->Prev = NULL;
	NewToken->type = type;
	NewToken->value = ft_strdup(value);
	if (!NewToken->value)
	{
		free(NewToken);
		return NULL;
	}
	return (NewToken);
}

void	add_token(t_token_list *TokenList, t_token *NewToken)
{
	if (!TokenList || !NewToken)
		return ;

	if (!TokenList->First)
	{
		TokenList->First = NewToken;
		TokenList->Last = NewToken;
	} else
	{
		NewToken->Prev = TokenList->Last;
		NewToken->Next = NULL;
		TokenList->Last->Next = NewToken;
		TokenList->Last = NewToken;
	}
	TokenList->size++;
}
