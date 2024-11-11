/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/11 09:33:21 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_first_token(t_t_list *t_list)
{
	return (!t_list->first || (t_list->last && (t_list->last->type == TOKEN_PIPE
				|| t_list->last->type == TOKEN_AND
				|| t_list->last->type == TOKEN_OR
				|| t_list->last->type == TOKEN_LPAREN)));
}

void	h_cmd_arg(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell)
{
	char	buffer[256];
	int		j;

	j = 0;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '>' && input[*i] != '<' && j < (int) sizeof(buffer) - 1
		&& input[*i] != '(' && input[*i] != ')')
	{
		buffer[j++] = input[(*i)++];
	}
	buffer[j] = '\0';
	if (is_first_token(t_list))
	{
		if (command_exists(buffer, shell))
			add_token(t_list, create_token(buffer, TOKEN_COMMAND));
		else
			add_token(t_list, create_token(buffer, TOKEN_ARGUMENT));
	}
	else
		add_token(t_list, create_token(buffer, TOKEN_ARGUMENT));
}

void	handle_and(uint16_t *i, t_t_list *t_list)
{
	add_token(t_list, create_token("&&", TOKEN_AND));
	(*i) += 2;
}

void	handle_wildcards(uint16_t *i, t_t_list *t_list)
{
	add_token(t_list, create_token("*", TOKEN_WILDCARDS));
	(*i)++;
}
