/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:48:27 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/29 15:35:47 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/debugger.h"

static const char *color_codes[] = {
	GREEN, GREEN, YELLOW, YELLOW, YELLOW,
	YELLOW, YELLOW, CYAN, CYAN, CYAN,
	CYAN, MAGENTA, MAGENTA, MAGENTA, RED
};

void	print_token_type(t_token_type type)
{
	const char	*types[] = {
		"Command", "Argument", "Pipe", "Redirection In", "Redirection Out",
		"Append", "Heredoc", "Variable", "String", "And", "Or",
		"End of File", "Wildcard", "Expand", "Unknown token type"
	};
	int	index;

	index = (type >= 0 && type <= TOKEN_EXPAND) ? type : TOKEN_EXPAND + 1;
	printf("%s%s%s", color_codes[index], types[index], RESET);
}

void	print_t_list(t_t_list *t_list)
{
	t_token			*token_cursor;
	unsigned int	index;

	if (!t_list || !t_list->first)
	{
		// printf(RED "Token list is empty.\n" RESET);
		return ;
	}
	printf(CYAN "\n== TOKEN LIST (" YELLOW "%u" CYAN " tokens) ==\n" RESET, t_list->size);
	token_cursor = t_list->first;
	index = 0;
	while (token_cursor)
	{
		printf(BLUE "Token %u:\n" RESET, index);
		printf("  " MAGENTA "Type   : " RESET);
		print_token_type(token_cursor->type);
		printf("\n  " MAGENTA "Value  : " RESET "\"%s\"", token_cursor->value);
		printf(CYAN "-----------------------------\n" RESET);
		token_cursor = token_cursor->next;
		index++;
	}
	printf(CYAN "== END OF TOKEN LIST ==\n\n" RESET);
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
