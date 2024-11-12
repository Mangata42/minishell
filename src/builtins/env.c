/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:24:40 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 15:21:00 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_sh *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->env_size - 1)
	{
		if (shell->env[i].title && shell->env[i].value)
		{
			ft_putstr_fd(shell->env[i].title, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(shell->env[i].value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
// -1 pour éviter l'entrée NULL finale