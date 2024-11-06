/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:22:16 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/06 22:29:38 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_shell(t_sh *shell)
{
	int	i;

	i = 0;
	while (i < shell->env_size)
	{
		free(shell->env[i].title);
		i++;
	}
	free(shell->env);
	free(shell);
	while (i < shell->env_size)
	{
		free(shell->env[i].title);
		i++;
	}
	free(shell->env);
	free(shell);
}
