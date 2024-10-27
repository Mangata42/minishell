/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:04:19 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 17:23:09 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void h_pipe(char *input, uint16_t *i, t_token_list *TokenList)
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

void h_rout(char *input, uint16_t *i, t_token_list *TokenList)
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

void h_rin(char *input, uint16_t *i, t_token_list *TokenList)
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

void h_s_q(char *input, uint16_t *i, t_token_list *TokenList)
{
	char buffer[256];
	uint16_t j = 0;

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

void	h_d_q(char *input, uint16_t *i, t_token_list *TokenList, t_shell *shell)
{
	char	buffer[256];
	size_t	j;

	j = 0;
	(*i)++;
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$')
		{
			if (j > 0)
			{
				buffer[j] = '\0';
				add_token(TokenList, create_token(ft_strdup(buffer), TOKEN_STRING));
				j = 0;
			}
			h_exp(input, i, TokenList, shell);
		}
		else
		{
			if (j < sizeof(buffer) - 1)
				buffer[j++] = input[*i];
			(*i)++;
		}
	}
	buffer[j] = '\0';
	if (j > 0)
		add_token(TokenList, create_token(ft_strdup(buffer), TOKEN_STRING));
	if (input[*i] == '\"')
		(*i)++;
	else
		printf("Error: Missing closing double quote\n");
}

