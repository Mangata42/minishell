/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   T_ListUtils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:27:26 by nghaddar          #+#    #+#             */
/*   Updated: 2024/10/26 20:37:51 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_t_list *init_t_list()
{
	t_t_list *NewT_List;

	NewT_List = malloc(sizeof(t_t_list));
	if (!NewT_List)
		return (NULL);
	
	NewT_List->first = NULL;
	NewT_List->last = NULL;
	NewT_List->size = 0;
	return (NewT_List);
}


void free_token_list(t_t_list *T_ListToFree)
{
	t_token *TokenCursor;
	t_token *ToFree;

	if (T_ListToFree) // if T_List actually exists
	{
		TokenCursor = T_ListToFree->first;
		while (TokenCursor)
		{
			ToFree = TokenCursor;
			TokenCursor = ToFree->next;
			if (ToFree->value) // to avoid double free or non-malloc'ed values
				free(ToFree->value);
			free(ToFree);
		}
		free(T_ListToFree);
	}
}

t_token *create_token(const char *value, t_token_type type)
{
	t_token *NewToken = malloc(sizeof(t_token));

	if (!NewToken)
		return (NULL);
	
	NewToken->next = NULL;
	NewToken->prev = NULL;
	NewToken->type = type;
	NewToken->value = ft_strdup(value);
	if (!NewToken->value)
	{
		free(NewToken);
		return NULL;
	}
	return (NewToken);
}

void	add_token(t_t_list *T_List, t_token *NewToken)
{
	if (!T_List || !NewToken)
		return ;

	if (!T_List->first)
	{
		T_List->first = NewToken;
		T_List->last = NewToken;
	} else
	{
		NewToken->prev = T_List->last;
		NewToken->next = NULL;
		T_List->last->next = NewToken;
		T_List->last = NewToken;
	}
	T_List->size++;
}
