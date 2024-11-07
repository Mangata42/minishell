/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:11:54 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/07 13:35:06 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
// #include "../../include/shell.h"

// int	ft_unset(char **args, t_sh *shell)
// {
// 	t_var	*new_env;
// 	size_t	i;
// 	size_t	y;

// 	i = 0;
// 	y = 0;
// 	new_env = malloc(sizeof(t_var) * (shell->env_size));
// 	while (shell->env[y].title)
// 	{
// 		if (ft_strcmp(shell->env[y].title, var_title) == 0)
// 		{
// 			free(shell->env[y].title);
// 			free(shell->env[y].value);
// 			y++;
// 		}
// 		if (!shell->env[y].title)
// 			break ;
// 		new_env[i].title = ft_strdup(shell->env[y].title);
// 		new_env[i].value = ft_strdup(shell->env[y].value);
// 		free(shell->env[y].title);
// 		free(shell->env[y].value);
// 		i++;
// 		y++;
// 	}
// 	free(shell->env);
// 	shell->env = new_env;
// }
