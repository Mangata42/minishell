/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:28 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/24 18:21:53 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// initialize_shell();
	char *rl;
	char **cmd;
	char *pwd;
	
	while (1)
	{
		rl = readline("minishell>");
		cmd = ft_split(rl, ' ');
		
		if (!strncmp(cmd[0], "cd", ft_strlen("cd")))
			if (builtin_cd(cmd[1]) == -1)
				perror("cd");

		if (!strncmp(cmd[0], "echo", ft_strlen("echo")))
			builtin_echo(cmd[1], 0);

		if (!strncmp(cmd[0], "pwd", ft_strlen("pwd"))){
			if (!(pwd = builtin_pwd()))
				perror("pwd");
			else{
				ft_putstr(builtin_pwd());
				ft_putchar('\n');
			}
		}
		
		free(cmd);

	}
	return (0);
}