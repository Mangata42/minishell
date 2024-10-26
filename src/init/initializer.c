/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:23:12 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 11:07:49 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	int	i;
	int	env_count;

	env_count = 0;
	i = 0;
	shell->exit_status = 0;
	while(envp[env_count])
	{
		env_count++;
	}
	shell->envp = ft_safe_malloc(sizeof(char *) * (env_count + 1));
	while (i < env_count)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[env_count] = NULL;
}

void	update_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
}