/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:04 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/24 17:14:55 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_list *lexer(char *input)
{
	t_token_list *tokens = NULL;
	int i = 0;

	i = 0;
	while (input[i])
	{
		if (isspace(input[i]))
		{
			i++;
			continue;
		}
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
		else
			handle_cmd_arg(input, &i, &tokens);
	}
	return tokens;
}
