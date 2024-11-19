/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:11:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/19 19:34:42 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/shell.h"

int	verify_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] == '_')
		i++;
	if (i == 0 && !ft_isalpha(arg[i]))
		return (1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

void	remove_var(t_sh *shell, char *var_title)
{
	t_var	*new_env;
	size_t	i;
	size_t	y;

	new_env = NULL;
	i = 0;
	y = 0;
	new_env = malloc(sizeof(t_var) * shell->env_size);
	if (!new_env)
		return ;
	while (i < shell->env_size - 1)
	{
		if (ft_strcmp(shell->env[i].title, var_title))
		{
			new_env[y].title = ft_strdup(shell->env[i].title);
			new_env[y].value = ft_strdup(shell->env[i].value);
			y++;
		}
		free(shell->env[i].title);
		free(shell->env[i].value);
		i++;
	}
	shell->env_size--;
	free(shell->env);
	shell->env = new_env;
}

int	ft_unset(char **args, t_sh *shell)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		if (verify_arg(args[i]))
		{
			printf("minishell: unset: `%s' not a valid identifier\n", args[i]);
			return (1);
		}
		if (!var_exists(shell, args[i]))
		{
			i++;
			continue ;
		}
		remove_var(shell, args[i]);
		i++;
	}
	return (0);
}
// if (!var_exists(shell, args[i])) //if variable does not exist,
// avoid useless copy
