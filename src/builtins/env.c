/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:24:40 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/06 22:17:52 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_sh *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->env_size - 1) // -1 pour éviter l'entrée NULL finale
	{
		if (shell->env[i].title && shell->env[i].value)
			printf("%s=%s\n", shell->env[i].title, shell->env[i].value);
		i++;
	}
	return (0);
}
