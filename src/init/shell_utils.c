/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:29:33 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/11 15:10:55 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**populate_arr(t_sh *shell, char **env_arr)
{
	size_t	i;
	size_t	y;
	size_t	z;

	i = 0;
	while (i < shell->env_size - 1)
	{
		y = 0;
		z = 0;
		env_arr[i] = malloc(ft_strlen(shell->env[i].title) + \
			ft_strlen(shell->env[i].value) + 2);
		while (shell->env[i].title[z])
			env_arr[i][y++] = shell->env[i].title[z++];
		env_arr[i][y++] = '=';
		z = 0;
		while (shell->env[i].value[z])
			env_arr[i][y++] = shell->env[i].value[z++];
		env_arr[i][y] = 0;
		i++;
	}
	return (env_arr);
}

char	**ret_env_array(t_sh *shell)
{
	char	**env_arr;

	env_arr = malloc(sizeof(char *) * (shell->env_size));
	if (!env_arr)
		return (NULL);
	env_arr = ft_memset(env_arr, 0, sizeof(char *) * (shell->env_size));
	env_arr = populate_arr(shell, env_arr);
	return (env_arr);
}
