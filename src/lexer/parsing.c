/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:04 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 10:55:35 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_whitespace(char c, int *i)
{
	if (ft_isspace(c))
	{
		(*i)++;
		return (true);
	}
	return (false);
}

t_token_list	*tokenize(char *input, t_token *tokens, int i, t_shell *shell)
{
	while (input[i])
	{
		if (is_whitespace(input[i], &i))
			continue ;
		if (input[i] == '|')
			handle_pipe(input, &i, &tokens);
		else if (input[i] == '>')
			handle_rout(input, &i, &tokens);
		else if (input[i] == '<')
			handle_rin(input, &i, &tokens);
		else if (input[i] == '\'')
			handle_single_quote(input, &i, &tokens);
		else if (input[i] == '\"')
			handle_double_quote(input, &i, &tokens);
		else if (input[i] == '&' && input[i + 1] == '&')
			handle_and(input, &i, &tokens);
		else if (input[i] == '*')
			handle_wildcards(input, &i, &tokens);
		else if (input[i] == '$')
			handle_expand(input, &i, &tokens, &shell);
		else
			handle_cmd_arg(input, &i, &tokens);
	}
	return (tokens);
}

t_token_list	*lexer(char *input, t_shell *shell)
{
	t_token_list	*tokens;

	tokens = NULL;
	tokens = tokenize(input, tokens, 0, &shell);
	return (tokens);
}
