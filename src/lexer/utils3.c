/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:36:26 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 18:21:06 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_brace_expand(char *input, uint16_t *i, t_t_list *T_List)
{
	char buffer[256];
	size_t j = 0;

	(*i)++;
	while (input[*i] && input[*i] != '}')
	{
		if (j < sizeof(buffer) - 1)
			buffer[j++] = input[*i];
		(*i)++;
	}
	if (input[*i] != '}')
	{
		printf("Error: Missing closing brace\n");
		return;
	}
	(*i)++;
	buffer[j] = '\0';

	char *word = strtok(buffer, " ");
	while (word != NULL)
	{
		add_token(T_List, create_token(word, TOKEN_EXPAND));
		word = strtok(NULL, " ");
	}
}

void	handle_alnum_expand(char *input, uint16_t *i, t_t_list *TokenList, char **envp)
{
	char	buffer[256];
	unsigned int	j;
	char	*value;

	j = 0;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		if (j < sizeof(buffer) - 1)
			buffer[j++] = input[*i];
		(*i)++;
	}
	buffer[j] = '\0';
	value = get_env_value(buffer, envp);
	if (value)
		add_token(TokenList, create_token(ft_strdup(value), TOKEN_EXPAND));
	else
		add_token(TokenList, create_token(ft_strdup(""), TOKEN_EXPAND));
}

void h_exp(char *input, uint16_t *i, t_t_list *T_List, t_sh *shell)
{
	(*i)++;
	if (input[*i] == '?')
	{
		char *status;

		status = ft_itoa(shell->exit_status);
		add_token(T_List, create_token(status, TOKEN_EXPAND));
		(*i)++;
	}
	else if (input[*i] == '{')
	{
		handle_brace_expand(input, i, T_List);
	}
	else
	{
		handle_alnum_expand(input, i, T_List, shell->envp);
	}
}
