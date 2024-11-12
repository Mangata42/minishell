/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:26:42 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/12 21:56:13 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_candies(t_sh *shell, t_ast_node *node)
{
	if (shell)
		free_shell(shell);
	if (node)
		free_ast(node);
}

int	ft_exit(char **args, t_sh *shell, t_ast_node *node)
{
	long long	exit_code;
	char		*endptr;

	endptr = NULL;
	printf("exit\n");
	if (!args[1])
	{
		free_candies(shell, node);
		exit(0);
	}
	exit_code = strtoll(args[1], &endptr, 10);
	if (*endptr != '\0' || args[1][0] == '\0')
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_candies(shell, node);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	free_candies(shell, node);
	exit((unsigned char)exit_code);
}
