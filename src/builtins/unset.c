/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:11:54 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/05 17:19:35 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/shell.h"

void	builtin_unset(t_sh *shell, char *var_title)
{
	t_var	*new_env;
	size_t	i = 0;
	size_t	y = 0;

	new_env = malloc(sizeof(t_var) * (shell->env_size));
	while (shell->env[y].title)
	{
		if (ft_strcmp(shell->env[y].title, var_title) == 0)
		{
			free(shell->env[y].title);
			free(shell->env[y].value);
			y++;
		}
		
		if (!shell->env[y].title) break;

		new_env[i].title = ft_strdup(shell->env[y].title);
		new_env[i].value = ft_strdup(shell->env[y].value);
		free(shell->env[y].title);
		free(shell->env[y].value);
		i++;
		y++;
	}
	free(shell->env);
	shell->env = new_env;
}