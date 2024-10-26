/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:28 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 21:15:37 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_token_list(t_token_list *list);

int	main(void)
{
	t_shell			Shell;
	t_token_list	*TokenList;
	extern char		**environ;

	initialize_shell(&Shell, environ);
	
	while (42)
	{
		char	*input;
		
		input = readline("minishell>");
		if (!input)
			break;
		if (*input)
			add_history(input);
		TokenList = lexer(input, &Shell);

		if (!TokenList)
			return (1);
			
		print_token_list(TokenList);
		free(input);
		free_token_list(TokenList);
		ft_putchar('\n');
	}
	write_history("history_file.txt");
	
	return (0);
}
