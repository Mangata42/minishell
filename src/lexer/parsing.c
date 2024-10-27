/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:04 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 18:02:14 by fflamion         ###   ########.fr       */
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

t_t_list	*lexer(char *input, t_sh *shell)
{
	t_t_list *T_List;
	uint16_t i = 0;

	if (!(T_List = init_t_list()))
		return (NULL);

	while (input[i])
	{
		while (is_whitespace(input[i], &i)) ;
		if (input[i] == '|')
			h_pipe(input, &i, T_List);
		else if (input[i] == '>')
			h_rout(input, &i, T_List);
		else if (input[i] == '<')
			h_rin(input, &i, T_List);
		else if (input[i] == '\'')
			h_s_q(input, &i, T_List);
		else if (input[i] == '\"')
			h_d_q(input, &i, T_List, shell);
		else if (input[i] == '&' && input[i + 1] == '&')
			handle_and(&i, T_List);
		else if (input[i] == '*')
			handle_wildcards(&i, T_List);
		else if (input[i] == '$')
			h_exp(input, &i, T_List, shell);
		else
			h_cmd_arg(input, &i, T_List);
	}
	return (T_List);
}
