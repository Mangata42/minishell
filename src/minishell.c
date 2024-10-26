/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:28 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 11:04:43 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	initialize_shell(&shell, envp);
	while (42)
	{
		char	*input;
		
		input = readline("minishell>");
		if (!input)
			break;
		if (*input)
			add_history(input);
		t_token_list *list = lexer(input, &shell);
		print_token_list(list);
		free(input);
		ft_putchar('\n');
	}
	write_history("history_file.txt");
}
