/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:14:57 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 22:32:07 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shelllevel(t_sh *shell)
{
	int		shlvl;
	char	*modvalue;
	size_t	i;

	i = -1;
	while (shell->envp[++i])
		free(shell->envp[i]);
	free(shell->envp);
	shlvl = ft_atoi(get_env_value(shell, "SHLVL"));
	modvalue = ft_itoa(++shlvl);
	mod_var(shell, "SHLVL", modvalue);
	shell->envp = ret_env_array(shell);
	free(modvalue);
}

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
	char	*input;

	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			free(input);
			free_shell(shell);
			ft_exit((char *[]){"exit", "127", NULL}, NULL, NULL);
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

int	main(int argc, char **argv, char **environ)
{
	t_sh	shell;

	if (argc != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	initialize_shell(&shell, environ);
	shelllevel(&shell);
	main_loop(&shell);
	free_shell(&shell);
	return (0);
}
