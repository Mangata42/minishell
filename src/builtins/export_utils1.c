/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:43:12 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/11 06:33:38 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/shell.h"

void	free_split(char **split_str)
{
	if (split_str)
	{
		if (split_str[0])
			free(split_str[0]);
		if (split_str[1])
			free(split_str[1]);
		free(split_str);
	}
}

void	swap_values(t_var *a, t_var *b)
{
	t_var	tmp;

	tmp.title = a->title;
	tmp.value = a->value;
	a->title = b->title;
	a->value = b->value;
	b->title = tmp.title;
	b->value = tmp.value;
}

t_var	*copy_env(t_sh *shell)
{
	t_var	*env_copy;
	size_t	i;
	size_t	env_size;

	i = 0;
	env_size = shell->env_size - 1;
	env_copy = malloc(sizeof(t_var) * (env_size + 1));
	if (!env_copy)
		return (NULL);
	while (i < env_size)
	{
		env_copy[i].title = ft_strdup(shell->env[i].title);
		if (!env_copy[i].title)
			break ;
		env_copy[i].value = ft_strdup(shell->env[i].value);
		if (!env_copy[i].value)
		{
			free(env_copy[i].title);
			break ;
		}
		i++;
	}
	env_copy[i].title = NULL;
	env_copy[i].value = NULL;
	return (env_copy);
}

t_var	*var_exists(t_sh *shell, char *var_to_check)
{
	size_t	i;

	i = 0;
	while (i < shell->env_size - 1)
	{
		if (ft_strcmp(shell->env[i].title, var_to_check) == 0)
			return (&shell->env[i]);
		i++;
	}
	return (NULL);
}
// size_t env_size = shell->env_size - 1;  Adjusted for zero-based index
