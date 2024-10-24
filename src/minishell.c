/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:28 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/24 14:46:28 by fflamion         ###   ########.fr       */
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
		t_sep *list = tokenizer(input);
		print_list(list);
		free(input);
		free_list(list);
		ft_putchar('\n');
	}
}