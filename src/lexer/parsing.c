/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:04 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 21:49:55 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_whitespace(char c, unsigned int *i)
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
	unsigned int i = 0;

	if (!(TokenList = init_token_list()))
		return (NULL);

	while (input[i])
	{
		while (is_whitespace(input[i], &i)) ;
		if (input[i] == '|')
			handle_pipe(input, &i, TokenList);
		else if (input[i] == '>')
			handle_rout(input, &i, TokenList);
		else if (input[i] == '<')
			handle_rin(input, &i, TokenList);
		else if (input[i] == '\'')
			handle_single_quote(input, &i, TokenList);
		else if (input[i] == '\"')
			handle_double_quote(input, &i, TokenList);
		else if (input[i] == '&' && input[i + 1] == '&')
			handle_and(&i, TokenList);
		else if (input[i] == '*')
			handle_wildcards(&i, TokenList);
		else if (input[i] == '$')
			handle_expand(input, &i, TokenList, shell);
		else
			handle_cmd_arg(input, &i, TokenList);
	}
	return (TokenList);
}
