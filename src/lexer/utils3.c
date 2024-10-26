/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:36:26 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 11:02:14 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_brace_expand(char *input, int *i, t_token **tokens)
{
	char buffer[256];
	int j = 0;

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
		add_token(tokens, create_token(ft_strdup(word), TOKEN_EXPAND));
		word = strtok(NULL, " ");
	}
}


void handle_alnum_expand(char *input, int *i, t_token **tokens)
{
	char buffer[256];
	int j = 0;

	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		if (j < sizeof(buffer) - 1)
			buffer[j++] = input[*i];
		(*i)++;
	}
	buffer[j] = '\0';
	if (j > 0)
		add_token(tokens, create_token(ft_strdup(buffer), TOKEN_EXPAND));
	else
		add_token(tokens, create_token(ft_strdup("$"), TOKEN_STRING));
}


void handle_expand(char *input, int *i, t_token **tokens, t_shell *shell)
{
	(*i)++;
	if (input[*i] == '?')
	{
		char *status;
		
		status = ft_itoa(shell->exit_status);
		add_token(tokens, create_token(status, TOKEN_EXPAND));
		(*i)++;
	}
	else if (input[*i] == '{')
	{
		handle_brace_expand(input, i, tokens);
	}
	else
	{
		handle_alnum_expand(input, i, tokens);
	}
}

