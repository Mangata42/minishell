/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:36:26 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 19:21:19 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	handle_brace_expand(char *input, int *i, t_token_list **tokens)
{
	char	buffer[256];
	int		j;
	char	**words;
	int		k;

	j = 0;
	(*i)++;
	while (input[*i] && input[*i] != '}')
	{
		if (j < sizeof(buffer) - 1)
			buffer[j++] = input[*i];
		(*i)++;
	}
	if (input[*i] != '}')
		return ((void)printf("Error: Missing closing brace\n"));
	(*i)++;
	buffer[j] = '\0';

	words = ft_split(buffer, ' ');
	if (!words)
		return;
	k = 0;
	while (words[k])
	{
		add_token(tokens, create_token(ft_strdup(words[k]), TOKEN_EXPAND));
		free(words[k]);
		k++;
	}
	free(words);
}


void	handle_alnum_expand(char *input, int *i, t_token_list **tokens, char **envp)
{
	char	buffer[256];
	int		j;
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
		add_token(tokens, create_token(ft_strdup(value), TOKEN_EXPAND));
	else
		add_token(tokens, create_token(ft_strdup(""), TOKEN_EXPAND));
}


void handle_expand(char *input, int *i, t_token_list **tokens, t_shell *shell)
{
	(*i)++;
	if (input[*i] == '?')
	{
		char *status;
		
		status = ft_itoa(shell->exit_status);
		if (!status)
			printf("gere le avant\n");
		add_token(tokens, create_token(status, TOKEN_EXPAND));
		(*i)++;
	}
	else if (input[*i] == '{')
		handle_brace_expand(input, i, tokens);
	else
		handle_alnum_expand(input, i, tokens, shell->envp);
}
