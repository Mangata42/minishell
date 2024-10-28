/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:04:19 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 18:29:15 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	h_pipe(char *input, uint16_t *i, t_t_list *t_list)
{
	if (input[*i + 1] == '|')
	{
		add_token(t_list, create_token("||", TOKEN_OR));
		(*i) += 2;
	}
	else
	{
		add_token(t_list, create_token("|", TOKEN_PIPE));
		(*i)++;
	}
}

void	h_rout(char *input, uint16_t *i, t_t_list *t_list)
{
	if (input[*i + 1] == '>')
	{
		add_token(t_list, create_token(">>", TOKEN_APPEND));
		(*i) += 2;
	}
	else
	{
		add_token(t_list, create_token(">", TOKEN_REDIRECTION_OUT));
		(*i)++;
	}
}

void	h_rin(char *input, uint16_t *i, t_t_list *t_list)
{
	if (input[*i + 1] == '<')
	{
		add_token(t_list, create_token("<<", TOKEN_HEREDOC));
		(*i) += 2;
	}
	else
	{
		add_token(t_list, create_token("<", TOKEN_REDIRECTION_IN));
		(*i)++;
	}
}

void	h_s_q(char *input, uint16_t *i, t_t_list *t_list)
{
	char		buffer[256];
	uint16_t	j;

	j = 0;
	(*i)++;
	while (input[*i] && input[*i] != '\'' && j < sizeof(buffer) - 1)
		buffer[j++] = input[(*i)++];
	buffer[j] = '\0';
	if (input[*i] == '\'')
	{
		add_token(t_list, create_token(buffer, TOKEN_STRING));
		(*i)++;
	}
	else
		fprintf(stderr, "Error: Missing closing single quote\n");
}

void	h_d_q(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell)
{
	char	buffer[256];
	size_t	j;

	j = 0;
	(*i)++;
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$' && j > 0)
		{
			buffer[j] = '\0';
			add_token(t_list, create_token(buffer, TOKEN_STRING));
			j = 0;
			h_exp(input, i, t_list, shell);
		}
		else if (j < sizeof(buffer) - 1)
			buffer[j++] = input[(*i)++];
	}
	buffer[j] = '\0';
	if (j > 0)
		add_token(t_list, create_token(buffer, TOKEN_STRING));
	if (input[*i] == '\"')
		(*i)++;
	else
		fprintf(stderr, "Error: Missing closing double quote\n");
}
