/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:07:26 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/05 18:35:55 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/shell.h"

void	print_sorted_env(t_sh *shell)
{
	t_var *sorted_end;
	size_t i = 0;
	size_t y = 0;
	
	sorted_end = malloc(sizeof(t_var) * (shell->env_size + 1));
	while (i < shell->env_size)
	{
		;
	}
}

void	mod_var(t_sh *shell, char *var_title, char *var_value)
{
	t_var *existing_value;

	existing_value = var_exists(shell, var_title);
	free(existing_value->value);
	existing_value->value = ft_strdup(var_value);
}

void	add_var(t_sh *shell, char *var_title, char *var_value)
{
	t_var	*new_env;
	size_t	i = 0;
	
	new_env = malloc(sizeof(t_var) * shell->env_size + 1);
	if (!new_env)
		return ;
	while (i < shell->env_size - 1)
	{
		new_env[i].title = ft_strdup(shell->env[i].title);
		new_env[i].value = ft_strdup(shell->env[i].value);
		free(shell->env[i].title);
		free(shell->env[i].value);
		i++;
	}
	new_env[i].title = ft_strdup(var_title);
	new_env[i].value = ft_strdup(var_value);
	new_env[i + 1].title = NULL;
	new_env[i + 1].value = NULL;
	shell->env_size++;
	free(shell->env);
	shell->env = new_env;
}	

void	builtin_export(t_sh *shell, char *new_var)
{
	char **split_str = NULL;

	if (!new_var)
		print_sorted_env(shell);
	if (!ft_strchr(new_var, '=') || !ft_isalpha(new_var[0]))
		printf("minishell: export: %s not a valid identifier\n", new_var);
	
	split_str = ft_split(new_var, '=');
	if (var_exists(shell, split_str[0])){
		ft_putstr("var exists.\n");
		mod_var(shell, split_str[0], split_str[1]);
	}
	else
		add_var(shell, split_str[0], split_str[1]);
	
	// free(split_str[0]);
	// free(split_str[1]);
	// free(split_str);
	return ;
}