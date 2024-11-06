/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:24:40 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/06 15:26:31 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_env(t_sh *shell)
{
	size_t i = 0;

	while (i < shell->env_size)
	{
		printf("%s=%s\n", shell->env[i].title, shell->env[i].value);
		i++;
	}
}