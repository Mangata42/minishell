/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:28 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/24 17:13:25 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// initialize_shell();
	char *rl;
	char *cwd = malloc(256);

	while (1){
		rl = readline("minishell>");
		builtin_cd(rl);
		cwd = getcwd(cwd, 256);
		printf("Current working directory : %s\n", cwd);
	}
	return (0);
}