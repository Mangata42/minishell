/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:07:26 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/04 17:58:28 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	print_env(t_sh *shell)
{
	//need to print alphabetic order
	
	char **env = shell->envp;

	while (*env)
		printf("%s\n", *env++);
}

void	add_var(t_sh *shell, char *new_var)
{
	char 	**env = shell->envp;
	char 	**new_env = NULL;
	uint16_t	arr_size = shell->env_entries;
	uint16_t	i = -1;

	new_env = malloc(sizeof(char *) * arr_size + 2);
	if (!new_env)
		return ;
	
	while (env[++i]){
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	
	new_env[i] = ft_strdup(new_var);
	new_env[++i] = NULL;
	shell->envp = new_env;
	free(env);
}	

void	export(t_sh *shell, char *new_var)
{
	if (!new_var)
	{
		print_env(shell);
		return ;
	}

	if (!ft_strchr(new_var, '=') || new_var[0] == '=')
	{
		printf("minishell: export: %s not a valid identifier\n", new_var);
		return ;
	}

	else
		add_var(shell, new_var);
}