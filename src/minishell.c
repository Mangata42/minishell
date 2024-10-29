/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:28 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/29 15:51:21 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_input(char *input, t_sh *shell)
{
	t_t_list	*t_list;

	t_list = lexer(input, shell);
	if (!t_list)
		return (1);
	parser(t_list);
	print_t_list(t_list);
	free_token_list(t_list);
	return (0);
}

void	main_loop(t_sh *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell>");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (process_input(input, shell))
		{
			free(input);
			break ;
		}
		free(input);
	}
}

int	main(void)
{
	t_sh			shell;
	extern char		**environ;

	// print_env(environ);
	initialize_shell(&shell, environ);
	main_loop(&shell);
	write_history("history_file.txt");
	return (0);
}
