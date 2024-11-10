/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/10 17:37:06 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Add this line at the top of your lexer.c file
static bool	is_start_of_command = true;

// Modify the h_cmd_arg function
void	h_cmd_arg(char *input, uint16_t *i, t_t_list *t_list, char **envp)
{
	char	buffer[256];
	int		j;

	j = 0;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '>' && input[*i] != '<' && j < (int)sizeof(buffer) - 1
		&& input[*i] != '(' && input[*i] != ')')
	{
		buffer[j++] = input[(*i)++];
	}
	buffer[j] = '\0';
	if (is_start_of_command)
	{
		is_start_of_command = false;
		if (command_exists(buffer, envp))
			add_token(t_list, create_token(buffer, TOKEN_COMMAND));
		else
			add_token(t_list, create_token(buffer, TOKEN_ARGUMENT));
	}
	else
	{
		add_token(t_list, create_token(buffer, TOKEN_ARGUMENT));
	}
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
