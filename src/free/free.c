/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:34:59 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/05 10:10:13 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_shell(t_sh *shell)
{
	int	i = 0;

	while (i < shell->env_size)
	{
		free(shell->env[i].title);
		free(shell->env[i].value);
		i++;
	}
	free(shell->env);
	free(shell);
}
