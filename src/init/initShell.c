/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initShell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:23:12 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 16:22:53 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void initialize_shell(t_shell *shell, char **envp)
{
	shell->exit_status = 0;
	shell->envp = envp;
}

void update_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
}

char	*get_env_value(const char *name, char **envp)
{
	int i;
	size_t len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return &envp[i][len + 1];
		i++;
	}
	return "";
}
