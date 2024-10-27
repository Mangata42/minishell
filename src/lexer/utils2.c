/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 17:21:23 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	h_cmd_arg(char *input, uint16_t *i, t_token_list *TokenList)
{
	char	buffer[256];
	int j;

	j = 0;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
		buffer[j++] = input[(*i)++];
	buffer[j] = '\0';
	add_token(TokenList, create_token(buffer, TOKEN_COMMAND));
}

void	handle_and(uint16_t *i, t_token_list *TokenList)
{
	add_token(TokenList, create_token("&&", TOKEN_AND));
	(*i) += 2;
}

void	handle_wildcards(uint16_t *i, t_token_list *TokenList)
{
	add_token(TokenList, create_token("*", TOKEN_WILDCARDS));
	(*i)++;
}