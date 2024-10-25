/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:04:19 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/25 12:14:11 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_pipe(char *input, int *i, t_token_list **tokens)
{
	if (input[*i + 1] == '|')
	{
		add_token(tokens, create_token(ft_strdup("||"), TOKEN_OR));
		(*i) += 2;
	}
	else
	{
	add_token(tokens, create_token(ft_strdup("|"), TOKEN_PIPE));
	(*i)++;
	}
}

void handle_rout(char *input, int *i, t_token_list **tokens)
{
	if (input[*i + 1] == '>')
	{
		add_token(tokens, create_token(ft_strdup(">>"), TOKEN_APPEND));
		(*i) += 2;
	}
	else
	{
		add_token(tokens, create_token(ft_strdup(">"), TOKEN_REDIRECTION_OUT));
		(*i)++;
	}
}

void handle_rin(char *input, int *i, t_token_list **tokens)
{
	if (input[*i + 1] == '<')
	{
		add_token(tokens, create_token(ft_strdup("<<"), TOKEN_HEREDOC));
		(*i) += 2;
	}
	else
	{
		add_token(tokens, create_token(ft_strdup("<"), TOKEN_REDIRECTION_IN));
		(*i)++;
	}
}

void handle_single_quote(char *input, int *i, t_token_list **tokens)
{
	char buffer[256];
	int j = 0;

	(*i)++;
	while (input[*i] && input[*i] != '\'')
		buffer[j++] = input[(*i)++];
	buffer[j] = '\0';
	if (input[*i] == '\'')
	{
		add_token(tokens, create_token(ft_strdup(buffer), TOKEN_STRING));
		(*i)++;
	}
	else
	{
		printf("Error: Missing closing single quote\n");
	}
}

void handle_double_quote(char *input, int *i, t_token_list **tokens)
{
	char buffer[256];
	int j = 0;

	(*i)++;
	while (input[*i] && input[*i] != '\"')
		buffer[j++] = input[(*i)++];
	buffer[j] = '\0';
	if (input[*i] == '\"')
	{
		add_token(tokens, create_token(ft_strdup(buffer), TOKEN_STRING));
		(*i)++;
	}
	else
	{
		printf("Error: Missing closing double quote\n");
	}
}
