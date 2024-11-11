/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:22:16 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/11 13:02:14 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_shell(t_sh *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->env_size)
	{
		free(shell->env[i].title);
		free(shell->env[i].value);
		i++;
	}
	free(shell->env);
	i = -1;
	while (shell->envp[++i])
		free(shell->envp[i]);
	free(shell->envp);
}
