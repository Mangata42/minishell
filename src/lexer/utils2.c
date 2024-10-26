/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 21:02:08 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_cmd_arg(char *input, unsigned int *i, t_token_list *TokenList)
{
	char	buffer[256];
	unsigned int j;

	j = 0;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
		buffer[j++] = input[(*i)++];
	buffer[j] = '\0';
	add_token(TokenList, create_token(buffer, TOKEN_COMMAND));
}

void	handle_and(unsigned int *i, t_token_list *TokenList)
{
	add_token(TokenList, create_token("&&", TOKEN_AND));
	(*i) += 2;
}

void	handle_wildcards(unsigned int *i, t_token_list *TokenList)
{
	add_token(TokenList, create_token("*", TOKEN_WILDCARDS));
	(*i)++;
}