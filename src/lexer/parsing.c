/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:04 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/28 14:39:47 by fflamion         ###   ########.fr       */
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

void	handle_token(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell)
{
	if (input[*i] == '|')
		h_pipe(input, i, t_list);
	else if (input[*i] == '>')
		h_rout(input, i, t_list);
	else if (input[*i] == '<')
		h_rin(input, i, t_list);
	else if (input[*i] == '\'')
		h_s_q(input, i, t_list);
	else if (input[*i] == '\"')
		h_d_q(input, i, t_list, shell);
	else if (input[*i] == '&' && input[*i + 1] == '&')
		handle_and(i, t_list);
	else if (input[*i] == '*')
		handle_wildcards(i, t_list);
	else if (input[*i] == '$')
		h_exp(input, i, t_list, shell);
	else
		h_cmd_arg(input, i, t_list);
}

t_t_list	*lexer(char *input, t_sh *shell)
{
	t_t_list	*t_list;
	uint16_t	i;

	i = 0;
	t_list = init_t_list();
	if (!t_list)
		return (NULL);
	while (input[i] && is_whitespace(input[i], &i))
		;
	if (input[i] == '\0')
		return (t_list);
	i = 0;
	while (input[i])
	{
		while (is_whitespace(input[i], &i))
			;
		handle_token(input, &i, t_list, shell);
	}
	return (t_list);
}
