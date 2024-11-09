/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:07:26 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/09 23:10:35 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/shell.h"

void	print_sorted_env(t_sh *shell)
{
	t_var	*env_copy;
	int		has_swapped;
	size_t	i;

	has_swapped = 1;
	i = 0;
	size_t env_size = shell->env_size - 1; // Adjusted for zero-based index
	env_copy = copy_env(shell);
	if (!env_copy)
		return ;
	while (has_swapped)
	{
		has_swapped = 0;
		while (i < env_size - 1)
		{
			if (ft_strcmp(env_copy[i].title, env_copy[i + 1].title) > 0)
			{
				swap_values(&env_copy[i], &env_copy[i + 1]);
				has_swapped = 1;
			}
			i++;
		}
		i = 0;
	}
	while (i < env_size)
	{
		printf("export %s=\"%s\"\n", env_copy[i].title, env_copy[i].value);
		i++;
	}
	i = 0;
	while (i < env_size)
	{
		free(env_copy[i].title);
		free(env_copy[i].value);
		i++;
	}
	free(env_copy);
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

static int	verify_arg(char *arg)
{
	size_t	i;
	char	**str_split;

	i = -1;
	str_split = NULL;
	str_split = ft_split(arg, '=');
	if (!str_split)
	{
		while (arg[++i])
		{
			if (!ft_isalnum(arg[i]))
			{
				printf("minishell: export: %s not a valid identifier\n", arg);
				return (1);
			}
		}
	}
	else
	{
		while (str_split[0][++i])
		{
			if (!ft_isalnum(str_split[0][i]))
			{
				printf("minishell: export: %s not a valid identifier\n", arg);
				free_split(str_split);
				return (1);
			}
		}
	}
	return (0);
}

int	ft_export(char **args, t_sh *shell)
{
	char **split_str = NULL;
	int status = 0;
	size_t i = 1;

	if (!args[i])
		print_sorted_env(shell);
	while (args[i])
	{
		if (verify_arg(args[i]))
			return (1);

		split_str = ft_split(args[i], '=');
		if (!split_str[1])
		{
			status = 0;
			break ;
		}
		if (var_exists(shell, split_str[0]))
		{
			mod_var(shell, split_str[0], split_str[1]);
		}
		else
			add_var(shell, split_str[0], split_str[1]);
		i++;
		free_split(split_str);
	}
	return (status);
}