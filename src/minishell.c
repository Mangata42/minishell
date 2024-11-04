/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:28 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/05 08:45:17 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_input(char *input, t_sh *shell)
{
	t_t_list	*t_list;
	t_ast_node	*ast_root;

	t_list = lexer(input, shell);
	if (!t_list)
		return (1);
	// print_t_list(t_list);
	parser(t_list);
	// if (parser(t_list))
	// {
	// 	free_token_list(t_list);
	// 	return (1);
	// }
	ast_root = ast_parser(t_list);
	// print_ast(ast_root, 0);
	execute_ast(ast_root, shell);
	free_ast(ast_root);
	free_token_list(t_list);
	return (0);
}

void	main_loop(t_sh *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			if (process_input(input, shell))
				break ;
		}
		free(input);
	}
}

int	main(void)
{
	t_sh		shell;
	extern char	**environ;

	setup_signals();
	initialize_shell(&shell, environ);
	main_loop(&shell);
	return (0);
}
