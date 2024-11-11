/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:48:27 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/11 03:57:58 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/debugger.h"
#include "../../include/minishell.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define Y "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void	print_token_type(t_token_type type)
{
	int			index;
	const char	*color_code;
	const char	*type_name;

	index = get_token_index(type);
	color_code = get_color_code(index);
	type_name = get_type(index);
	printf("%s%s%s", color_code, type_name, RESET);
}

void	print_token_info(t_token *token, unsigned int index)
{
	printf(BLUE "Token %u:\n" RESET, index);
	printf("  " MAGENTA "Type   : " RESET);
	print_token_type(token->type);
	printf("\n  " MAGENTA "Value  : " RESET "\"%s\"\n", token->value);
	printf(CYAN "-----------------------------\n" RESET);
}

void	print_t_list(t_t_list *t_list)
{
	t_token			*token_cursor;
	unsigned int	index;

	printf(CYAN "\n==TOKEN LIST(" Y "%u" CYAN " tokens)==\n" RESET,
		t_list->size);
	token_cursor = t_list->first;
	index = 0;
	while (token_cursor)
	{
		print_token_info(token_cursor, index);
		token_cursor = token_cursor->next;
		index++;
	}
	printf(CYAN "== END OF TOKEN LIST ==\n\n" RESET);
}
