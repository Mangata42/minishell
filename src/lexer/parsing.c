/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:04 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 17:23:09 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_whitespace(char c, uint16_t *i)
{
	if (ft_isspace(c))
	{
		(*i)++;
		return (true);
	}
	return (false);
}

t_token_list	*lexer(char *input, t_shell *shell)
{
	t_token_list *TokenList;
	uint16_t i = 0;

	if (!(TokenList = init_token_list()))
		return (NULL);

	while (input[i])
	{
		while (is_whitespace(input[i], &i)) ;
		if (input[i] == '|')
			h_pipe(input, &i, TokenList);
		else if (input[i] == '>')
			h_rout(input, &i, TokenList);
		else if (input[i] == '<')
			h_rin(input, &i, TokenList);
		else if (input[i] == '\'')
			h_s_q(input, &i, TokenList);
		else if (input[i] == '\"')
			h_d_q(input, &i, TokenList, shell);
		else if (input[i] == '&' && input[i + 1] == '&')
			handle_and(&i, TokenList);
		else if (input[i] == '*')
			handle_wildcards(&i, TokenList);
		else if (input[i] == '$')
			h_exp(input, &i, TokenList, shell);
		else
			h_cmd_arg(input, &i, TokenList);
	}
	return (TokenList);
}
