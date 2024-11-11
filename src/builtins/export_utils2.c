/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 06:44:30 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/11 08:57:32 by nghaddar         ###   ########.fr       */
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
