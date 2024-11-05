/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initShell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:23:12 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/05 17:04:36 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_base_env(t_sh *shell)
{
	shell->env = malloc(sizeof(t_var) * 4);
	if (!shell->env)
		return ;
	
	shell->env[0].title = ft_strdup("PWD");
	shell->env[0].value = getcwd(NULL, 0);
	shell->env[1].title = ft_strdup("SHLVL");
	shell->env[1].value = ft_strdup("1");
	shell->env[2].title = ft_strdup("_");
	shell->env[2].value = ft_strdup("/usr/bin/env");
	shell->env[3].title = NULL;
	shell->env[3].value = NULL;
	shell->env_size = 4;
	return ;
}

void	parse_env(t_sh *shell, char **envp)
{
	char	**split_str;
	size_t	i = 0;

	while (envp[i++]) ; 
	shell->env = malloc(sizeof(t_var) * (i + 1));
	shell->env_size = i;
	i = 0;
	while (*envp)
	{
		split_str = ft_split(*envp, '=');
		shell->env[i].title = ft_strdup(split_str[0]);
		shell->env[i].value = ft_strdup(split_str[1]);
		free(split_str[0]);
		free(split_str[1]);
		free(split_str);
		*envp++;
		i++;
	}
	shell->env[i].title = NULL;
	shell->env[i].value = NULL;
}

void	initialize_shell(t_sh *shell, char **envp)
{
	if (!*envp)
		create_base_env(shell);
	
	else
		parse_env(shell, envp);
	
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
