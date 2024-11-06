/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:43:12 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/06 16:07:27 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/shell.h"

void	swap_values(t_var *a, t_var *b)
{
	t_var tmp;

    tmp.title = a->title;
    tmp.value = a->value;
    a->title = b->title;
    a->value = b->value;
    b->title = tmp.title;
    b->value = tmp.value;
}

t_var	*remove_var(t_var *env, char *var_title)
{
	t_var	*new_env = NULL;
	size_t	i = 0;
	size_t	y = 0;
	size_t	env_size = 0;


	while (env[env_size].title)
		env_size++;;

	new_env = malloc(sizeof(t_var) * (env_size));
	while (env[y].title)
	{
		if (ft_strcmp(env[y].title, var_title) == 0)
		{
			free(env[y].title);
			free(env[y].value);
			y++;
		}
		
		if (!env[y].title) break;

		new_env[i].title = ft_strdup(env[y].title);
		new_env[i].value = ft_strdup(env[y].value);
		free(env[y].title);
		free(env[y].value);
		i++;
		y++;
	}
	free(env);
	return (new_env);
}

t_var	*copy_env(t_sh *shell)
{
	t_var	*env_copy;
	size_t	i = 0;

	env_copy = malloc(sizeof(t_var) * shell->env_size + 1);
	if (!env_copy)
		return (NULL);
	
	while (i < shell->env_size - 1)
	{
		env_copy[i].title = ft_strdup(shell->env[i].title);
		env_copy[i].value = ft_strdup(shell->env[i].value);
		i++;
	}
	env_copy[i].title = NULL;
	env_copy[i].value = NULL;
	return (env_copy);
}

t_var	*var_exists(t_sh *shell, char *var_to_check)
{
	char **split_str;
	size_t i = 0;

	split_str = ft_split(var_to_check, '=');
	while (i < shell->env_size)
	{
		if (ft_strcmp(shell->env[i].title, split_str[0]) == 0)
			return (&shell->env[i]);
		i++;
	}

	return (NULL);
}

