/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:07:26 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/11 14:01:10 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/shell.h"

static int	verify_arg(char *arg)
{
	size_t	i;

	if (!ft_isalpha(arg[0]))
	{
		printf("minishell: export: %s not a valid identifier\n", arg);
		return (1);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]))
		{
			printf("minishell: export: %s not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	if (!ft_strchr(arg, '='))
		return (1);
	return (0);
}

void	mod_var(t_sh *shell, char *var_title, char *var_value)
{
	t_var	*existing_value;

	existing_value = var_exists(shell, var_title);
	free(existing_value->value);
	existing_value->value = ft_strdup(var_value);
}

void	add_var(t_sh *shell, char *var_title, char *var_value)
{
	t_var	*new_env;
	size_t	i;

	i = 0;
	new_env = malloc(sizeof(t_var) * (shell->env_size + 1));
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

int	process_export_arg(char *arg, t_sh *shell)
{
	char	**split_str;

	if (verify_arg(arg))
		return (1);
	split_str = ft_split(arg, '=');
	if (!split_str[1])
	{
		ft_free_split(split_str);
		return (0);
	}
	if (var_exists(shell, split_str[0]))
		mod_var(shell, split_str[0], split_str[1]);
	else
		add_var(shell, split_str[0], split_str[1]);
	ft_free_split(split_str);
	return (0);
}

int	ft_export(char **args, t_sh *shell)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	if (!args[i])
	{
		print_sorted_env(shell);
		return (0);
	}
	while (args[i])
	{
		status = process_export_arg(args[i], shell);
		if (status)
			return (status);
		i++;
	}
	i = -1;
	while (shell->envp[++i])
		free(shell->envp[i]);
	free(shell->envp);
	shell->envp = ret_env_array(shell);
	return (status);
}

// int	ft_export(char **args, t_sh *shell)
// {
// 	char	**split_str;
// 	int		status;
// 	size_t	i;

// 	split_str = NULL;
// 	status = 0;
// 	i = 1;
// 	if (!args[i])
// 		print_sorted_env(shell);
// 	while (args[i])
// 	{
// 		if (verify_arg(args[i]))
// 			return (1);
// 		split_str = ft_split(args[i], '=');
// 		if (!split_str[1])
// 		{
// 			ft_free_split(split_str);
// 			status = 0;
// 			break ;
// 		}
// 		if (var_exists(shell, split_str[0]))
// 		{
// 			mod_var(shell, split_str[0], split_str[1]);
// 		}
// 		else
// 			add_var(shell, split_str[0], split_str[1]);
// 		i++;
// 		free_split(split_str);
// 	}
// 	return (status);
// }
// void	print_sorted_env(t_sh *shell)
// {
// 	t_var	*env_copy;
// 	int		has_swapped;
// 	size_t	i;

// 	has_swapped = 1;
// 	i = 0;
// 	size_t env_size = shell->env_size - 1; // Adjusted for zero-based index
// 	env_copy = copy_env(shell);
// 	if (!env_copy)
// 		return ;
// 	while (has_swapped)
// 	{
// 		has_swapped = 0;
// 		while (i < env_size - 1)
// 		{
// 			if (ft_strcmp(env_copy[i].title, env_copy[i + 1].title) > 0)
// 			{
// 				swap_values(&env_copy[i], &env_copy[i + 1]);
// 				has_swapped = 1;
// 			}
// 			i++;
// 		}
// 		i = 0;
// 	}
// 	while (i < env_size)
// 	{
// 		printf("export %s=\"%s\"\n", env_copy[i].title, env_copy[i].value);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < env_size)
// 	{
// 		free(env_copy[i].title);
// 		free(env_copy[i].value);
// 		i++;
// 	}
// 	free(env_copy);
// }
