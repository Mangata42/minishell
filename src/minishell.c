/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:28 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/25 12:06:30 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// initialize_shell();
	while (42)
	{
		char	*input;
		
		input = readline("minishell>");
		if (!input)
			break;
		if (*input)
			add_history(input);
		t_token_list *list = lexer(input);
		print_token_list(list);
		free(input);
		ft_putchar('\n');
	}
	write_history("history_file.txt");
}
