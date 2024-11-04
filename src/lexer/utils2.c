/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/04 13:45:45 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	h_cmd_arg(char *input, uint16_t *i, t_t_list *t_list, char **envp)
{
	char	buffer[256];
	int		j;

	j = 0;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '|' && input[*i] != '>'
		&& input[*i] != '<' && j < (int) sizeof(buffer) - 1
		&& input[*i] != '(' && input[*i] != ')')
	{
		buffer[j++] = input[(*i)++];
	}
	buffer[j] = '\0';
	if (command_exists(buffer, envp))
		add_token(t_list, create_token(buffer, TOKEN_COMMAND));
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
