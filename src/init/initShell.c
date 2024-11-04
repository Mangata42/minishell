/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initShell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:23:12 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/04 16:25:01 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initialize_shell(t_sh *shell, char **envp)
{
	size_t	i = -1;
	size_t	y = -1;
	char	*old_str_p = NULL;

	if (!*envp){
		shell->envp = malloc(sizeof(char *) * 4);
		shell->envp[0] = getcwd(NULL, 0);
		old_str_p = shell->envp[0];
		shell->envp[0] = ft_strpreppend(shell->envp[0], "PWD=");
		free(old_str_p);
		shell->envp[1] = ft_strdup("SHLVL=1");
		shell->envp[2] = ft_strdup("_=/usr/bin/env");
		shell->envp[3] = NULL;
		shell->env_entries = 3;
		return ;
	}
	
	while (envp[++i]) ;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	shell->env_entries = i;
	
	while (++y < i)
		shell->envp[y] = ft_strdup(envp[y]);
		
	shell->envp[y] = NULL;
	shell->exit_status = 0;
}

void	update_exit_status(t_sh *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
}

char	*get_env_value(const char *name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}
