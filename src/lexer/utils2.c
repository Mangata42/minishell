/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/25 12:06:15 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_cmd_arg(char *input, int *i, t_token_list **tokens)
{
	char	buffer[256];
	int		j;

	j = 0;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
		buffer[j++] = input[(*i)++];
	buffer[j] = '\0';
	add_token(tokens, create_token(ft_strdup(buffer), TOKEN_COMMAND));
}

void	handle_and(char *input, int *i, t_token_list **tokens)
{
	add_token(tokens, create_token(ft_strdup("&&"), TOKEN_AND));
	(*i) += 2;
}

void	handle_wildcards(char *input, int *i, t_token_list **tokens)
{
	add_token(tokens, create_token(ft_strdup("*"), TOKEN_WILDCARDS));
	(*i)++;
}

t_token *create_token(const char *value, t_token_type type)
{
	t_token *new_token = malloc(sizeof(t_token));
	if (!new_token)
		return NULL;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return NULL;
	}
	new_token->type = type;
	return new_token;
}

void add_token(t_token_list **tokens, t_token *new_token)
{
	if (!tokens || !new_token)
		return;
	t_token_list *new_node = malloc(sizeof(t_token_list));
	if (!new_node)
		return;
	new_node->token = new_token;
	new_node->next = NULL;
	if (!(*tokens))
	{
		new_node->prev = NULL;
		*tokens = new_node;
	}
	else
	{
		t_token_list *last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
}
