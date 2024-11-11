/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 06:44:30 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/11 10:26:34 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sort_env_copy(t_var *env_copy, size_t env_size)
{
	int		has_swapped;
	size_t	i;

	has_swapped = 1;
	while (has_swapped)
	{
		has_swapped = 0;
		i = 0;
		while (i < env_size - 1)
		{
			if (ft_strcmp(env_copy[i].title, env_copy[i + 1].title) > 0)
			{
				swap_values(&env_copy[i], &env_copy[i + 1]);
				has_swapped = 1;
			}
			i++;
		}
	}
}

static void	print_env_vars(t_var *env_copy, size_t env_size)
{
	size_t	i;

	i = 0;
	while (i < env_size)
	{
		printf("export %s=\"%s\"\n", env_copy[i].title, env_copy[i].value);
		i++;
	}
}

static void	free_env_copy(t_var *env_copy, size_t env_size)
{
	size_t	i;

	i = 0;
	while (i < env_size)
	{
		free(env_copy[i].title);
		free(env_copy[i].value);
		i++;
	}
	free(env_copy);
}

void	print_sorted_env(t_sh *shell)
{
	t_var	*env_copy;
	size_t	env_size;

	env_size = shell->env_size - 1;
	env_copy = copy_env(shell);
	if (!env_copy)
		return ;
	sort_env_copy(env_copy, env_size);
	print_env_vars(env_copy, env_size);
	free_env_copy(env_copy, env_size);
}

char 	**ret_env_array(t_sh *shell)
{
	char	**env_arr;
	size_t i;
	size_t y;
	size_t z;

	env_arr = malloc(sizeof(char *) * shell->env_size);
	if (!env_arr)
		return (NULL);
	i = 0;
	while (i < shell->env_size - 1)
	{
		y = 0;
		z = 0;
		env_arr[i] = malloc(ft_strlen(shell->env[i].title) + ft_strlen(shell->env[i].value) + 2);
		while (shell->env[i].title[z])
			env_arr[i][y++] = shell->env[i].title[z++];
		env_arr[i][y++] = '=';
		z = 0;
		while (shell->env[i].value[z])
			env_arr[i][y++] = shell->env[i].value[z++];
		env_arr[i][y] = 0;
		i++;
	}

	env_arr[i] = NULL;
	return (env_arr);
}
