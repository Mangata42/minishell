/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/12 03:22:56 by fflamion         ###   ########.fr       */
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
	if (parser(t_list))
	{
		free_token_list(t_list);
		return (0);
	}
	ast_root = ast_parser(t_list, shell);
	free_token_list(t_list);
	execute_ast(ast_root, shell);
	free_ast(ast_root);
	return (0);
}

void	main_loop(t_sh *shell)
{
	char			*input;

	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			free(input);
			free_shell(shell);
			ft_exit((char *[]){"exit", "127", NULL});
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (process_input(input, shell))
			{
				free(input);
				break ;
			}
		}
		free(input);
	}
}

int	main(void)
{
	t_sh		shell;
	extern char	**environ;

	initialize_shell(&shell, environ);
	main_loop(&shell);
	free_shell(&shell);
	return (0);
}
