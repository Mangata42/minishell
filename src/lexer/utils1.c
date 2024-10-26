/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:04:19 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 21:04:37 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_pipe(char *input, unsigned int *i, t_token_list *TokenList)
{
	if (input[*i + 1] == '|')
	{
		add_token(TokenList, create_token("||", TOKEN_OR));
		(*i) += 2;
	}
	else
	{
		add_token(TokenList, create_token("|", TOKEN_PIPE));
		(*i)++;
	}
}

void handle_rout(char *input, unsigned int *i, t_token_list *TokenList)
{
	if (input[*i + 1] == '>')
	{
		add_token(TokenList, create_token(">>", TOKEN_APPEND));
		(*i) += 2;
	}
	else
	{
		add_token(TokenList, create_token(">", TOKEN_REDIRECTION_OUT));
		(*i)++;
	}
}

void handle_rin(char *input, unsigned int *i, t_token_list *TokenList)
{
	if (input[*i + 1] == '<')
	{
		add_token(TokenList, create_token("<<", TOKEN_HEREDOC));
		(*i) += 2;
	}
	else
	{
		add_token(TokenList, create_token("<", TOKEN_REDIRECTION_IN));
		(*i)++;
	}
}

void handle_single_quote(char *input, unsigned int *i, t_token_list *TokenList)
{
	char buffer[256];
	unsigned int j = 0;

	(*i)++;
	while (input[*i] && input[*i] != '\'')
		buffer[j++] = input[(*i)++];
	buffer[j] = '\0';
	if (input[*i] == '\'')
	{
		add_token(TokenList, create_token(buffer, TOKEN_STRING));
		(*i)++;
	}
	else
	{
		printf("Error: Missing closing single quote\n");
	}
}

void handle_double_quote(char *input, unsigned int *i, t_token_list *TokenList)
{
	char buffer[256];
	unsigned int j = 0;

	(*i)++;
	while (input[*i] && input[*i] != '\"')
		buffer[j++] = input[(*i)++];
	buffer[j] = '\0';
	if (input[*i] == '\"')
	{
		add_token(TokenList, create_token(buffer, TOKEN_STRING));
		(*i)++;
	}
	else
	{
		printf("Error: Missing closing double quote\n");
	}
}
