/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:01:31 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/06 22:19:51 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/debugger.h"
#include "../../include/minishell.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

int	get_token_index(t_token_type type)
{
	const t_token_type	token_types[] = {TOKEN_COMMAND, TOKEN_ARGUMENT,
		TOKEN_PIPE, TOKEN_REDIRECTION_IN, TOKEN_REDIRECTION_OUT,
		TOKEN_APPEND, TOKEN_HEREDOC, TOKEN_VARIABLE, TOKEN_STRING,
		TOKEN_AND, TOKEN_OR, TOKEN_EOF, TOKEN_WILDCARDS, TOKEN_EXPAND,
		TOKEN_INCONNU, TOKEN_LPAREN, TOKEN_RPAREN};
	int					i;

	i = 0;
	while (i < (int)(sizeof(token_types) / sizeof(token_types[0])))
	{
		if (type & token_types[i])
			return (i);
		i++;
	}
	return (-1);
}

const char	*get_color_code(int index)
{
	const char	*color_codes[] = {GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW,
		YELLOW, CYAN, CYAN, CYAN, CYAN, MAGENTA, MAGENTA, MAGENTA, RED,
		BLUE, BLUE};

	if (index >= 0 && index < (int)(sizeof(color_codes)
		/ sizeof(color_codes[0])))
		return (color_codes[index]);
	return (RESET);
}

const char	*get_type(int index)
{
	const char	*types[] = {"Command", "Argument", "Pipe", "Redirection In",
		"Redirection Out", "Append", "Heredoc", "Variable", "String", "And",
		"Or", "End of File", "Wildcard", "Expand", "Unknown token type",
		"Left Parenthesis", "Right Parenthesis"};

	if (index >= 0 && index < (int)(sizeof(types) / sizeof(types[0])))
		return (types[index]);
	return ("Unknown Type");
}

const char	*get_color(int level)
{
	const char	*colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

	return (colors[level % 7]);
}
