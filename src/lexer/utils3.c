/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:36:26 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 20:55:09 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_brace_expand(char *input, unsigned int *i, t_token_list *TokenList)
{
	char buffer[256];
	unsigned int j = 0;

	(*i)++;
	while (input[*i] && input[*i] != '}')
	{
		if (j < sizeof(buffer) - 1)
			buffer[j++] = input[*i];
		(*i)++;
	}
	if (input[*i] != '}')
	{
		printf("Error: Missing closing brace\n");
		return;
	}
	(*i)++;
	buffer[j] = '\0';

	char *word = strtok(buffer, " ");
	while (word != NULL)
	{
		add_token(TokenList, create_token(word, TOKEN_EXPAND));
		word = strtok(NULL, " ");
	}
}


void handle_alnum_expand(char *input, unsigned int *i, t_token_list *TokenList)
{
	char buffer[256];
	unsigned int j = 0;

	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		if (j < sizeof(buffer) - 1)
			buffer[j++] = input[*i];
		(*i)++;
	}
	buffer[j] = '\0';
	if (j > 0)
		add_token(TokenList, create_token(buffer, TOKEN_EXPAND));
	else
		add_token(TokenList, create_token("$", TOKEN_STRING));
}


void handle_expand(char *input, unsigned int *i, t_token_list *TokenList, t_shell *shell)
{
	(*i)++;
	if (input[*i] == '?')
	{
		char *status;
		
		status = ft_itoa(shell->exit_status);
		add_token(TokenList, create_token(status, TOKEN_EXPAND));
		(*i)++;
	}
	else if (input[*i] == '{')
	{
		handle_brace_expand(input, i, TokenList);
	}
	else
	{
		handle_alnum_expand(input, i, TokenList);
	}
}

